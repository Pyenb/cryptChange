@RD /S /Q "C:\Temp"
REG DELETE "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run" /v "Windows System Uptime" /f
taskkill /f /im "manager.exe"