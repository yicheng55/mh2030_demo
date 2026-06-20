$content = Get-Content 'D:\prg\davicom\mh2xxxx_proj\mh2030_demo\ModuleDemo\DM9051A\USER\DM9051A_lwip.uvprojx' -Raw
$paths = [regex]::Matches($content, '<FilePath>(.*?)</FilePath>') | ForEach-Object { $_.Groups[1].Value }
$dups = $paths | Group-Object | Where-Object { $_.Count -gt 1 }
Write-Host "Found $($dups.Count) duplicate file paths"
$dups | ForEach-Object { Write-Host "  $($_.Count)x : $($_.Name)" }
