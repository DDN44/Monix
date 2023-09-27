$File = './os.img'
$Filesize = ((Get-Item $File).length)
$Img = 1474560
$Imgsize = ($Img - $Filesize)
Remove-Item $File
Start-Sleep -Seconds 2
Copy-Item ./build/boot.o $File
Start-Sleep -Seconds 2
fsutil file seteof $File $Img
fsutil file setzerodata offset=$Filesize length=$Imgsize $File
