from cryptography.fernet import Fernet
import base64

# Fixed AES encryption key (32 bytes long)
key = Fernet.generate_key()
print("key=%s"%(key)) 
key_bstr=base64.b64encode(key).decode()
print("key bstr:", key_bstr) 
key_text = base64.b64decode(key_bstr.encode())
print("key original text:", key_text) 
#key = b'ftCIgpQ6lJu6KgFMtLx3Mm2Byf-pKgVdnShvLLLanOs='

cipher_suite = Fernet(key)

# Text to be encrypted
plaintext = "Avail rocks!"

# Encode the text
encoded_text = plaintext.encode()

# Encrypt the text
encrypted_text = cipher_suite.encrypt(encoded_text)

#print("Original Text:", plaintext)
#print("Encrypted Text:", encrypted_text)

b_str = base64.b64encode(encrypted_text).decode()
print("encrypted_byte_str=%s"%(b_str))

encrypted_text = base64.b64decode(b_str.encode())
# Decrypt the text
decrypted_text = cipher_suite.decrypt(encrypted_text)
decoded_text = decrypted_text.decode()

print("Decrypted Text:", decoded_text)
