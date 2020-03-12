# IPSec
In computing, Internet Protocol Security (IPsec) is a secure network protocol
suite that authenticates and encrypts the packets of data to provide secure
encrypted communication between two computers over an Internet Protocol network.
It is used in virtual private networks (VPNs). 


# Security architecture
The IPsec is an open standard as a part of the IPv4 suite. IPsec uses the
following protocols to perform various functions.

Authentication Headers (AH) provides connectionless data integrity and 
data origin authentication for IP datagrams and provides protection against replay attacks.

Encapsulating Security Payloads (ESP) provides confidentiality, connectionless 
data integrity, data-origin authentication, an anti-replay service (a form of 
partial sequence integrity), and limited traffic-flow confidentiality.[1]
    
Security Associations (SA) provides the bundle of algorithms and data that provide 
the parameters necessary for AH and/or ESP operations. The Internet Security Association 
and Key Management Protocol (ISAKMP) provides a framework for authentication and key 
exchange,[12] with actual authenticated keying material provided either by manual 
configuration with pre-shared keys, Internet Key Exchange (IKE and IKEv2), Kerberized 
Internet Negotiation of Keys (KINK), or IPSECKEY DNS records.


