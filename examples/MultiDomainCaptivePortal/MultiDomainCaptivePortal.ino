#include <ESP8266WiFi.h>
#include <MultiDomainDNSServer.h>
#include <ESP8266WebServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
IPAddress googleIP(192, 168, 1, 2);
IPAddress youtubeIP(192, 168, 1, 3);
IPAddress redditIP(192, 168, 1, 4);
MultiDomainDNSServer dnsServer;
ESP8266WebServer webServer(80);

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("MultiDomainDNSServer example");

  Serial.begin(9600);

  // modify TTL associated  with the domain name (in seconds)
  // default is 60 seconds
  dnsServer.setTTL(300);
  // set which return code will be used for all other domains (e.g. sending
  // ServerFailure instead of NonExistentDomain will reduce number of queries
  // sent by clients)
  // default is DNSReplyCode::NonExistentDomain

  String domains[] = {"google.com", "youtube.com", "reddit.com", "*"};
  IPAddress addrs[] = {googleIP, youtubeIP, redditIP, apIP};
  dnsServer.start(DNS_PORT, domains, addrs, 4);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // start DNS server for a specific domain name

  // simple HTTP server to see that DNS server is working
  webServer.onNotFound([]() {
    String message = "Hello World!\n\n";
    message += "URI: ";
    message += webServer.uri();

    webServer.send(200, "text/plain", message);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}