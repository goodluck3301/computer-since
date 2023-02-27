# The Difference Between Encoding, Encryption and Hashing.

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*6560dhphPktqoj03iF68PQ.jpeg)

There is a lot of buzz around data protection and security in our daily lives. We live in a time where it is not wrong to say that the Data is the new “Currency”. And just like any other currency that we own, we would never want our data to get into the possession of someone else, especially someone with wrong intentions. If you believe that your personal data is safe online, then trust me my friend, you can not be more wrong./<br>

Well, to be honest, most of you who are reading this probability are already aware about this fact (if you’re not then, Hello! Wake Up!). You might also have heard about the words written in the Title of this article i.e ```Encoding```, ```Encryption``` and ```Hashing```. It is a common misconception that these words refer to the same thing, but in reality they refer to their own techniques, which are way different from one another. So let’s wear our curiosity hats and try to understand what they actually are.

## Encoding

So first, let’s get the things straight, unlike Encryption and Hashing, Encoding is not used to security purpose. It is a technique in which the data is transformed from one format into another, so that it can be understood and consumed by different systems. There is no use of any “Key” in encoding. The same algorithm is used to decode the data which was used to encode it in the first place. Because of this reason, it is very easy for an attacker to decode the data if they have the possession of the encoded data. The example of such algorithms are ASCII, Unicode, Base64 etc.

#### Why do we even need Encoding?

To understand this, lets take an example of BASE64 encoding technique. During the initial years of emails, the data was mostly text based. So to transmit it over the internet, the text data was converted to Binary format, and at the receiver’s end, this binary data was again converted back to text format. But as time passed, the need to send attachments as well as multimedia along with the text based email came into existence. The probability of the Binary data of these attachments to get corrupted was high in it’s raw form. This was mainly because the Raw Binary contains some characters which in some languages are treated differently. For instance, in C/C++ the “Null” character is treated as the end of the file. So sending binary data containing “Null” bytes will eventually stop the file from being read completed and will cause data corruption. To tackle this issue, BASE64 encoding technique came into picture.

#### How does Base64 Encoding works?

Let’s take an Example of converting “abc” into Base64.</br>

1. Convert the characters in the string into decimal.

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*ICEVkBOmlun48DShKrmMvA.png)

a = 97, b = 98 and c = 99.

2. Convert each of these decimal numbers into their equivalent 8-bit Binary form:</br>

a = 0110 0001, b = 0110 0010 and c = 0110 0011</br>
i.e. abc = 0110 0001 0110 0010 0110 0011

3. Separate them into groups of 6-bit each:</br>

011000 — 010110 — 001001 — 100011</br>

4. Convert each Binary into their equivalent Decimal form:</br>

011000 = 24, 010110 = 22, 001001 = 9 and 100011 = 35</br>

5. Using the Base64 table, convert each of these decimal numbers into their corresponding Base64 characters:</br>

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*mFChZhmG3xTibRyiw9Qv7Q.png)

So, 24 = ‘Y’, 23 = ‘X’, 9 = ‘J’ and 35 = ‘j’. </br>
Therefore, “abc” => “YXJj” in Base64. </br>

Note: Sometimes it is impossible to divide the combined Binary into exact groups of 6 bits each. In that case, 0 is added in the end to make it an exact number of groups of 64 bits. This process is called as “Padding”. To encode the padded the data, if there are 6 fully padded bits, then it is mapped to “=”.
Example: “a:aa” => 011000 010011 101001 100001 011000 01xxxx xxxxxx xxxxxx => “YTphYQ==”

## Encryption

One can not imagine the internet without Encryption. The Internet would have been a way less secure place without it. The Data on the internet is kept confidential and secure using Encryption. Encryption makes the data unreadable and difficult to decode for an attacker and prevents it to be stolen.</br>

Encryption makes use of “Cryptographic Keys”. Using the key, the data is Encrypted at the sender’s end and using the same or different key, the data is Decrypted at the receiver's end. Based on the type of the Key being used for encrypting/decrypting the information, Encryption is classified into two categories:

- Symmetric Key Encryption
- Asymmetric Key Encryption

Let’s look into these two types of Encryption techniques:

### Symmetric Key:

The Symmetric Key Cryptography approach is straight forward. Before sending out the data over to the receiver, the sender uses a Private key to cipher the data. This Private Key is known only to the Sender and the Receiver. So, once the receiver gets the encrypted data, he or she uses the sender’s same private key to decrypt it. Since the sender and the receiver uses the same key, this is known as “Symmetric Key” cryptography.

![](https://miro.medium.com/v2/resize:fit:1100/1*SunS90u-6kikCjpPHy-jnA.gif)


Yes, there are plenty of benefit of using this technique for encryption, for instance, the simplicity of this system provides a logistical advantage as it requires less computing power. Also, just by increasing the length of the key can easily help in scaling up the security level of the system. But the problem of using this technique is already visible to us. How is the receiver going to know what is the secret key using which the data was encrypted at the first place? For him to know the key, the sender has to send the Key as well. Got the problem? Yes!! The sender has to transmit the key to the receiver as well, and if it is done over an unsecured connection, there is a high chance that they key can be intercepted by any attacker.</br>

### Asymmetric Key:

To counter the problems of using Symmetric Key Cryptography technique, the Asymmetric Key Cryptography technique is used. It is a relatively new technique compared to the previous one. As you can guess from the name itself, this technique involves two different keys. One key is used for encrypting the data, which is known as the Public Key, and is known virtually everyone on the internet. The other key is used for decrypting the data, which is known as the Private Key, and is known only to the receiver and it must be kept discreet. Therefor the use of two distinct keys, makes the system more secure and it becomes way too difficult for an attacker to crack it.

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*9xNAhOXjJV34Os2mis-ZWQ.jpeg)

The Public and Private keys are real Keys to a lock. These are basically two very large Prime Numbers that are mathematically related to one another. I.e. Whatever is encrypted by the Public Key, can only be decrypted by the related Private Key.
One can not simply guess the Private key based on knowing the Public Key.</br>

### Hashing
Do you know what is a blockchain developer’s favorite breakfast item? — It’s Hash Browns. (Ba Dun Tss)!
Okay, Jokes aside, Hashing is the process of ensuring the Integrity of the information being sent over the network. By that, it means that it makes sure that even if a single thing is changed, you can know that it is changed. Hashing protects your data against potential alteration so that your data isn’t changed even one bit.</br>

A Hash is basically a string that is generated from the input string by passing it through a Hash Algorithm. This hashed string is always of a fixed length no matter what is the size of the input string. Hashing can also be considered as “One Way Encryption” i.e. the data once hashed can never be reversed back to it’s original form.

#### How does the Hashing Algorithm Works?

“Behind every successful hash algorithm, there is a great hash function” — Some nerd on the Internet.
</br>

The Hash function lies at the heart of the Hashing algorithm. This hash function takes in data at a fixed-length, so the input is provided to the function by dividing the input into fixed-sized blocks. These blocks are called as ```Data Blocks```. If the size of input data is less than the size of the block, then ```Padding``` is used.

![](https://miro.medium.com/v2/resize:fit:720/format:webp/1*EDVapUv_XZcaa6g2-cn5Bw.png)

The Process of Hashing is also known as “Avalanche Effect”. It is as follows:
The message is processed one block at a time. The input is provided to the first block, the output of the first block is then given to the function along with second block’s input. Following the same process for the third block, where the output of the second block is given to the function along with the third block’s input. The final output is the combined value of all the blocks.
This way, if a single bit is changed or manipulated anywhere in between the message, the entire hash value will change.</br>

Some Popular Hashing Algorithms are:
- Message Digest (MD) Algorithm
- Secure Hash Algorithm (SHA)
- RACE Integrity Primitives Evaluation Message Digest (RIPEMD)
- Whirlpool
- Cyclic Redundancy Check (CRC)

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*MnVwldLagNoecLf4oYc7LA.png)

To flashback a bit:
- Encoding is a process of conversion of data from one format to another.
- Encryption is a process to convert the information into a cipher using keys, to maintain the confidentiality.
- Hashing is a technique to ensure the integrity of the data by converting it into a fixed-length string.

