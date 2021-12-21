from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

gauth = GoogleAuth()
gauth.LocalWebserverAuth()

drive = GoogleDrive(gauth)

file2 = drive.CreateFile()
file2.SetContentFile('kimenet.csv')
file2.Upload()
print('Created file %s with mimeType %s' % (file2['kimenet'],
file2['mimeType']))
