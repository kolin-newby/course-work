# Kolin Newby, Michael Hasenkamp
# kone9079, miha5997

import sys
from urllib import parse as ps
from pymd5 import md5, padding

def main(argv):
	sanity_check = "https://project1.ecen4133.org/kone9079/lengthextension/api?token="
	if len(argv) != 1 or sanity_check not in argv[0]:
		print("Arguments entered incorrectly!")
		return
	given_url = argv[0]

	tok_commands = given_url.split("token=")[1] #everything in the url after "token="
	temp = tok_commands.split("&", 1)
	m = temp[0] #original token
	given_commands = temp[1] #original commands
	
	m_len = 8 + (len(given_commands)) #length of secret + len of original commands (len of original md5 prehash value) 
	bits = (m_len + len(padding(m_len * 8))) * 8 #number of bits to tell md5 to ignore in new hash
	h = md5(state = bytes.fromhex(m), count = bits)

	ext = "command=UnlockSafes"
	h.update("&" + ext)
	new_token = h.hexdigest()
	original_pad = padding(64 + len(given_commands) * 8) #padding of original pre hash value to make url accurate
	new_url = given_url.split("token=")[0] + "token=" + new_token + "&" + given_commands + ps.quote(original_pad) + "&" + ext

	print(new_url)


if __name__ == "__main__":
	main(sys.argv[1:])