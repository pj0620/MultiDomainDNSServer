# MultiDomainDNSServer
extension of ESP8266 DNSServer that allows the server to store the ip address for multiple domains.

## Issue with DNSServer
In the stock DNSServer library for the ESP8266, only one domain name can be associated with one IP Address. For example, one could associate "example.com" with the IP Address 192.168.1.1. However, this becomes an issue when one wants to associate multiple domain names with multiple IP Addresses. Consider the following table. 

| domain        | IP Address    |
| ------------- | ------------- |
| google.com    | 192.168.1.2   |
| youtube.com   | 192.168.1.3   |
| reddit.com    | 192.168.1.4   |

It would be impossible to implement this domain name to IP Address mapping using the stock DNSServer library. This is possible with the MultiDomainDNSServer library. This exact example can be found [here](examples\MultiDomainDNSServer.ino). 

## Redirecting all DNS Queries
If one wants to redirect all domains to the same IP Address, use the "*" domain name. Just like the DNSServer library. However, this flag must be the **last** domain name listed. See the simple Captive Portal example. 
