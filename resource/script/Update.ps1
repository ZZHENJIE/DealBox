$WordArt = @'
      ___           ___           ___           ___       ___           ___           ___     
     /\  \         /\  \         /\  \         /\__\     /\  \         /\  \         |\__\    
    /::\  \       /::\  \       /::\  \       /:/  /    /::\  \       /::\  \        |:|  |   
   /:/\:\  \     /:/\:\  \     /:/\:\  \     /:/  /    /:/\:\  \     /:/\:\  \       |:|  |   
  /:/  \:\__\   /::\~\:\  \   /::\~\:\  \   /:/  /    /::\~\:\__\   /:/  \:\  \      |:|__|__ 
 /:/__/ \:|__| /:/\:\ \:\__\ /:/\:\ \:\__\ /:/__/    /:/\:\ \:|__| /:/__/ \:\__\ ____/::::\__\
 \:\  \ /:/  / \:\~\:\ \/__/ \/__\:\/:/  / \:\  \    \:\~\:\/:/  / \:\  \ /:/  / \::::/~~/~   
  \:\  /:/  /   \:\ \:\__\        \::/  /   \:\  \    \:\ \::/  /   \:\  /:/  /   ~~|:|~~|    
   \:\/:/  /     \:\ \/__/        /:/  /     \:\  \    \:\/:/  /     \:\/:/  /      |:|  |    
    \::/__/       \:\__\         /:/  /       \:\__\    \::/__/       \::/  /       |:|  |    
     ~~            \/__/         \/__/         \/__/     ~~            \/__/         \|__|  
'@

$UpdatePath = 'C:\Users\zhong\AppData\Local\DealBox\cache\update'
$UpdateZipPath = 'C:\Users\zhong\AppData\Local\DealBox\cache\update.zip'
$ZipSourcePath = 'C:\Users\zhong\AppData\Local\DealBox\cache\update\DealBox'
$ParentDir = Split-Path -Parent $PSScriptRoot

Write-Output $WordArt

Remove-Item -Path $UpdatePath

Expand-Archive -Path $UpdateZipPath -DestinationPath $UpdatePath

Write-Output "`n��ѹ���,��ʼ����..."

if(Copy-Item -Path $ZipSourcePath -Destination $ParentDir -Recurse -Force -PassThru){
      Write-Output "`n�������,�س�����DealBox"
      pause
      Start-Process "DealBox.exe"
}
