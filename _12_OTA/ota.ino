#include <WiFi.h>
#include <Update.h>

long contentLength = 0;
bool isValidContentType = false;

String host = "tuservidor.net";
String bin = "/openexpo/test.ino.bin";

String ota_get_header_value(String header, String headerName) {
  return header.substring(strlen(headerName.c_str()));
}

void ota_check_version() {
  WiFiClient ota_check_version;
  unsigned long timeout;

  Serial.println("Connecting to: " + String(host));
  if (ota_check_version.connect(host.c_str(), 80)) {
    Serial.println("Fetching Bin: " + String(bin));
    ota_check_version.print(String("GET ") + bin + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" +
                            "Cache-Control: no-cache\r\n" +
                            "Connection: close\r\n\r\n");

    timeout = millis();
    while (ota_check_version.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        ota_check_version.stop();
        return;
      }
    }

    while (ota_check_version.available()) {
      String line = ota_check_version.readStringUntil('\n');
      line.trim();

      if (!line.length()) {
        break; // and get the OTA started
      }

      if (line.startsWith("HTTP/1.1")) {
        if (line.indexOf("200") < 0) {
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          break;
        }
      }

      if (line.startsWith("Content-Length: ")) {
        contentLength = atol((ota_get_header_value(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      if (line.startsWith("Content-Type: ")) {
        String contentType = ota_get_header_value(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream") {
          isValidContentType = true;
        }
      }
    }
  }
  else {
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
  }

  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  if (contentLength && isValidContentType) {
    Serial.println("VALE.... TENEMOS UN NUMERO DE VERSION");
  }

  ota_check_version.stop();

}

void ota_timer() {
  static unsigned long t = 0;

  if (millis() - t > 10000) {
    t = millis();
    ota_exec();
  }
}

void ota_exec() {

  WiFiClient ota_client;

  unsigned long timeout;

  Serial.println("Connecting to: " + String(host));
  if (ota_client.connect(host.c_str(), 80)) {
    Serial.println("Fetching Bin: " + String(bin));
    ota_client.print(String("GET ") + bin + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Cache-Control: no-cache\r\n" +
                     "Connection: close\r\n\r\n");

    timeout = millis();
    while (ota_client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        ota_client.stop();
        return;
      }
    }

    while (ota_client.available()) {
      String line = ota_client.readStringUntil('\n');
      line.trim();

      if (!line.length()) {
        break; // and get the OTA started
      }

      if (line.startsWith("HTTP/1.1")) {
        if (line.indexOf("200") < 0) {
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          break;
        }
      }

      if (line.startsWith("Content-Length: ")) {
        contentLength = atol((ota_get_header_value(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      if (line.startsWith("Content-Type: ")) {
        String contentType = ota_get_header_value(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream") {
          isValidContentType = true;
        }
      }
    }
  }
  else {
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
  }

  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  if (contentLength && isValidContentType) {
    bool canBegin = Update.begin(contentLength);

    if (canBegin) {
      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
      // No activity would appear on the Serial monitor
      // So be patient. This may take 2 - 5mins to complete
      size_t written = Update.writeStream(ota_client);

      if (written == contentLength) {
        Serial.println("Written : " + String(written) + " successfully");
      }
      else {
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
        // retry??
        // ota_exec();
      }

      if (Update.end()) {
        Serial.println("OTA done!");
        if (Update.isFinished()) {
          Serial.println("Update successfully completed. Rebooting.");
          ESP.restart();
        }
        else {
          Serial.println("Update not finished? Something went wrong!");
        }
      }
      else {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
      }
    }
    else {
      // not enough space to begin OTA
      // Understand the partitions and
      // space availability
      Serial.println("Not enough space to begin OTA");
      ota_client.flush();
    }
  }
  else {
    Serial.println("There was no content in the response");
    //ota_client.flush();
    //ota_client.stop(); //¿?
  }
}

