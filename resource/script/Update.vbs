Dim title, message, style, response

title = "更新程序"
message = "请确保关闭DealBox程序:"
style = vbQuestion + vbYesNo

response = MsgBox(message, style, title)

Select Case response
    Case vbYes 
        Set objShell = WScript.CreateObject("WScript.Shell")
        objShell.Run "powershell.exe -NoExit -File Update.ps1"
End Select