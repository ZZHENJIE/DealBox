Dim title, message, style, response

title = "���³���"
message = "��ȷ���ر�DealBox����:"
style = vbQuestion + vbYesNo

response = MsgBox(message, style, title)

Select Case response
    Case vbYes 
        Set objShell = WScript.CreateObject("WScript.Shell")
        objShell.Run "powershell.exe -NoExit -File Update.ps1"
End Select