# MultiDomainDNSServer
Extension of ESP8266 [DNSServer](https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer) library that allows the DNS Server to translate multiple domain names into multiple IP Addresses.

## Issue with DNSServer
In the stock [DNSServer](https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer) library for the ESP8266, only one domain name can be associated with one IP Address. For example, one could associate "example.com" with the IP Address 192.168.1.1. However, this becomes an issue when one wants to associate multiple domain names with multiple IP Addresses. Consider the following table. 

| domain        | IP Address    |
| ------------- | ------------- |
| google.com    | 192.168.1.2   |
| youtube.com   | 192.168.1.3   |
| reddit.com    | 192.168.1.4   |

It would be impossible to implement this domain name to IP Address mapping using the standard DNSServer library. This is possible with the MultiDomainDNSServer library. This exact example can be found [here](https://github.com/pj0620/MultiDomainDNSServer/blob/master/examples/MultiDomainCaptivePortal/MultiDomainCaptivePortal.ino). 

## Redirecting all DNS Queries
To redirect all domain names to the same IP Address, use the "*" domain name just like the DNSServer library. To see an example of this, check [here](examples/CaptivePortal/CaptivePortal.ino).

## Redirect all but some DNS Queries 
In this case, one wants to route all traffic to a Captive Portal **except** a certian set of domain names. Consider the following table. 

| domain        | IP Address    |
| ------------- | ------------- |
| google.com    | 192.168.1.2   |
| youtube.com   | 192.168.1.3   |
| reddit.com    | 192.168.1.4   |
|      *        | 192.168.1.1   |    

For the the domains "google.com", "youtube.com", and "reddit.com", a predefined IP Address is given for each domain name. Then all other DNS Queries are given the IP Address of our access point(192.168.1.1). See this example [here](examples/MultiDomainCaptivePortal/MultiDomainCaptivePortal.ino).

#### Note: Always place the default IP at the **end** of the domain name list when calling start().

This will work.
```cpp
String domains[] = {"google.com", "youtube.com", "reddit.com", "*"};
IPAddress addrs[] = {googleIP, youtubeIP, redditIP, apIP};
dnsServer.start(DNS_PORT, domains, addrs, 4);
```

This will **not** work.
```cpp
String domains[] = {"google.com", "youtube.com", "*", "reddit.com"};
IPAddress addrs[] = {googleIP, youtubeIP, apIP, redditIP};
dnsServer.start(DNS_PORT, domains, addrs, 4);
```
