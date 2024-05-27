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

Write-Output "`n解压完成,开始更新..."

if(Copy-Item -Path $ZipSourcePath -Destination $ParentDir -Recurse -Force -PassThru){
      Write-Output "`n更新完成,回车启动DealBox"
      pause
      Start-Process "DealBox.exe"
}
