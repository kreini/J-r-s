import requests


url = 'http://192.168.43.55:5000/success'
files = {'file': open('MIT_License.txt', 'rb')}

r = requests.post(url, files=files)

#with open('teszt.txt', 'rb') as f:
#    a = requests.post('http://localhost:5000', data=f)
print(r.text)

#print(r.text)
