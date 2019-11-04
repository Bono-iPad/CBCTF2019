---
Key_check
---

Attacks for Small RSA public exponent are really dangerous. But I heard that some of our employees are using keys with small public exponents. That's ridiculous! I won't allow keys with public exponent = 65537 & 512 < modulus < 8192 bit! I made a small program for check RSA keys and running on my flag server. All employees should check their keys!! It's very small and simple program, so there will be no security issue and flag won't be stolen.

---
Usage
---

1) First, input your public key end with period.
2) Second, input your private key end with period.
3) The result will appear. If the message is broken, your key is bad. Throw it away.
4) If your have another key, type "y" + [ENTER] to continue. Otherwise, type "n" + [ENTER] to exit.
5) Repeat.

---
Example
---

$ nc key_check_server 12345
Please input your public key: 
-----BEGIN RSA PUBLIC KEY-----
(snip)
-----END RSA PUBLIC KEY-----
.
Key test: Give me your private key!
-----BEGIN RSA PRIVATE KEY-----
(snip)
-----END RSA PRIVATE KEY-----
.
128
Decryption complete.
If you see this message, your RSA key is valid!
continue?(y/n)
y
Please input your public key: 

(repeat...)

---
Caution
---

Only PKCS#1 RSA Public keys are allowed.


