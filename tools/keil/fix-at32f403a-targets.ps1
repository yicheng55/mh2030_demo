param(
    [string]$LwipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_lwip.uvprojx",
    [string]$UipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_uip.uvprojx",
    [string]$BaseProjectFile = "ModuleDemo/DM9051A/USER/DM9051A.uvprojx"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Add-FileToGroupText {
    param([string[]]$Lines, [int]$InsertAfterLine, [string]$FileName, [string]$FilePath)

    $indent = '          '
    $fileIndent = '            '
    $innerIndent = '              '

    $newLines = @(
        "$fileIndent<File>",
        "$innerIndent<FileName>$FileName</FileName>",
        "$innerIndent<FileType>1</FileType>",
        "$innerIndent<FilePath>$FilePath</FilePath>",
        "$innerIndent<FileOption>",
        "$innerIndent  <CommonProperty>",
        "$innerIndent    <IncludeInBuild>1</IncludeInBuild>",
        "$innerIndent  </CommonProperty>",
        "$innerIndent</FileOption>",
        "$fileIndent</File>"
    )

    $result = New-Object System.Collections.Generic.List[string]
    for ($i = 0; $i -lt $Lines.Count; $i++) {
        $result.Add($Lines[$i])
        if ($i -eq $InsertAfterLine) {
            foreach ($nl in $newLines) {
                $result.Add($nl)
            }
        }
    }
    return $result.ToArray()
}

function Set-IncludeInBuild {
    param([string[]]$Lines, [int]$TargetStart, [int]$TargetEnd, [string]$FileName, [int]$Value)

    for ($i = $TargetStart; $i -le $TargetEnd; $i++) {
        if ($Lines[$i] -match "<FileName>$([regex]::Escape($FileName))</FileName>") {
            for ($j = $i; $j -le $TargetEnd -and $j -lt $Lines.Length; $j++) {
                if ($Lines[$j] -match '<IncludeInBuild>') {
                    $Lines[$j] = $Lines[$j] -replace '<IncludeInBuild>[^<]*</IncludeInBuild>', "<IncludeInBuild>$Value</IncludeInBuild>"
                    Write-Host "  Set $FileName IncludeInBuild=$Value" -ForegroundColor $(if ($Value -eq 0) { 'DarkYellow' } else { 'DarkGreen' })
                    return ,$Lines
                }
                if ($Lines[$j] -match '<IncludeInBuild\s*/?>') {
                    $Lines[$j] = "                <IncludeInBuild>$Value</IncludeInBuild>"
                    Write-Host "  Set $FileName IncludeInBuild=$Value" -ForegroundColor $(if ($Value -eq 0) { 'DarkYellow' } else { 'DarkGreen' })
                    return ,$Lines
                }
                if ($Lines[$j] -match '</File>') {
                    $indent = $Lines[$j] -replace '^(\s*).*', '$1'
                    $foIndent = $indent.Substring(0, [Math]::Max(0, $indent.Length - 2))
                    $insertLines = @(
                        "${foIndent}<FileOption>",
                        "${foIndent}  <CommonProperty>",
                        "${foIndent}    <IncludeInBuild>$Value</IncludeInBuild>",
                        "${foIndent}  </CommonProperty>",
                        "${foIndent}</FileOption>"
                    )
                    $Lines = $Lines[0..($j-1)] + $insertLines + $Lines[$j..($Lines.Length-1)]
                    Write-Host "  Set $FileName IncludeInBuild=$Value (added)" -ForegroundColor $(if ($Value -eq 0) { 'DarkYellow' } else { 'DarkGreen' })
                    return ,$Lines
                }
            }
            Write-Warning "  Cannot set IncludeInBuild for $FileName (no scope)"
            return ,$Lines
        }
    }
    return ,$Lines
}

function Find-TargetRange {
    param([string[]]$Lines, [string]$TargetName)

    $start = -1
    $end = -1
    $inTarget = $false
    $depth = 0

    for ($i = 0; $i -lt $Lines.Length; $i++) {
        $line = $Lines[$i]

        if (-not $inTarget) {
            if ($line -match "<TargetName>$([regex]::Escape($TargetName))</TargetName>") {
                $inTarget = $true
                # Find the opening <Target> tag that contains this name
                for ($j = $i; $j -ge 0; $j--) {
                    if ($Lines[$j] -match '<Target>') {
                        $start = $j
                        break
                    }
                }
            }
        } else {
            if ($line -match '</Target>') {
                $end = $i
                break
            }
        }
    }

    return @{ Start = $start; End = $end }
}

function Fix-At32TargetText {
    param([string]$ProjectPath, [string]$TargetName, [array]$FilesToAdd)

    if (-not (Test-Path -LiteralPath $ProjectPath)) {
        Write-Warning "  Project not found: $ProjectPath"
        return
    }

    Write-Host "`nFixing $TargetName in $ProjectPath ..." -ForegroundColor Cyan
    Write-Host "  (text-based, preserves formatting)" -ForegroundColor DarkGray

    $originalContent = Get-Content -LiteralPath $ProjectPath -Raw
    $lines = @($originalContent -split "`r`n|`n")
    $range = Find-TargetRange -Lines $lines -TargetName $TargetName

    if ($range.Start -eq -1) {
        Write-Warning "  Target '$TargetName' not found"
        return
    }

    Write-Host "  Target range: lines $($range.Start)-$($range.End)" -ForegroundColor DarkGray
    $modified = $false

    # ---- 1. Fix Device ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<Device>') {
            $lines[$i] = $lines[$i] -replace '<Device>[^<]*</Device>', '<Device></Device>'
            Write-Host "  Cleared Device" -ForegroundColor DarkGray
            $modified = $true
            break
        }
    }

    # ---- 2. Fix Vendor ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<Vendor>') {
            $lines[$i] = $lines[$i] -replace '<Vendor>[^<]*</Vendor>', '<Vendor></Vendor>'
            Write-Host "  Cleared Vendor" -ForegroundColor DarkGray
            $modified = $true
            break
        }
    }

    # ---- 3. Fix Cpu ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<Cpu>') {
            $lines[$i] = '          <Cpu>CPUTYPE("Cortex-M4") ESEL ELITTLE</Cpu>'
            Write-Host "  Set Cpu=Cortex-M4" -ForegroundColor DarkGray
            $modified = $true
            break
        }
    }

    # ---- 4. Fix PackID and PackURL ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<PackID>') {
            $lines[$i] = $lines[$i] -replace '<PackID>[^<]*</PackID>', '<PackID></PackID>'
            $modified = $true
        }
        if ($lines[$i] -match '<PackURL>') {
            $lines[$i] = $lines[$i] -replace '<PackURL>[^<]*</PackURL>', '<PackURL></PackURL>'
            $modified = $true
        }
    }

    # ---- 5. Fix FlashDriverDll, RegisterFile, SFDFile ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<FlashDriverDll>') {
            $lines[$i] = '          <FlashDriverDll></FlashDriverDll>'
            $modified = $true
        }
        if ($lines[$i] -match '<RegisterFile>') {
            $lines[$i] = $lines[$i] -replace '<RegisterFile>[^<]*</RegisterFile>', '<RegisterFile></RegisterFile>'
            $modified = $true
        }
        if ($lines[$i] -match '<SFDFile>') {
            $lines[$i] = $lines[$i] -replace '<SFDFile>[^<]*</SFDFile>', '<SFDFile></SFDFile>'
            $modified = $true
        }
    }

    # ---- 6. Fix AdsCpuType ----
    for ($i = $range.Start; $i -le $range.End; $i++) {
        if ($lines[$i] -match '<AdsCpuType>') {
            $lines[$i] = $lines[$i] -replace '"Cortex-M0"', '"Cortex-M4"'
            Write-Host "  Set AdsCpuType=Cortex-M4" -ForegroundColor DarkGray
            $modified = $true
            break
        }
    }

    # ---- 7. Exclude MH2030A files ----
    $excludeFiles = @(
        'main.c', 'main_uip_mh2030a.c', 'main_uip_mh2030a_smoke.c',
        'main_uip_mh2030a_demo.c', 'main_dm9051_lwip_example.c',
        'mh20xx_it.c', 'system_mh20xx.c', 'startup_mh20xx.s',
        'mh2030a_dm9051_spi.c', 'mh2030a_dm9051_spi_dma.c', 'mh2030a_dm9051_int.c',
        'mh2030a_board.c', 'mh2030a_uip_clock.c', 'dm9051_hal_mh2030a_spi1.c',
        'dm9051_hal_mh2030a_spi1_dma.c', 'dm9051_hal_mh2030a_int.c'
    )

    foreach ($fname in $excludeFiles) {
        $lines = Set-IncludeInBuild -Lines $lines -TargetStart $range.Start -TargetEnd $range.End -FileName $fname -Value 0
    }

    # ---- 8. Include delay.c ----
    $lines = Set-IncludeInBuild -Lines $lines -TargetStart $range.Start -TargetEnd $range.End -FileName "delay.c" -Value 1

    # ---- 9. Add AT32F403A files to groups ----
    foreach ($entry in $FilesToAdd) {
        $groupName = $entry[0]
        $fileName = $entry[1]
        $filePath = $entry[2]

        # Find the group within target range
        $groupStart = -1
        $groupEnd = -1
        $inGroup = $false

        for ($i = $range.Start; $i -le $range.End; $i++) {
            $line = $lines[$i]

            if (-not $inGroup) {
                if ($line -match "<GroupName>$([regex]::Escape($groupName))</GroupName>") {
                    $inGroup = $true
                    # Find opening <Group>
                    for ($j = $i; $j -ge $range.Start; $j--) {
                        if ($lines[$j] -match '<Group>') {
                            $groupStart = $j
                            break
                        }
                    }
                }
            } else {
                if ($line -match '</Group>') {
                    $groupEnd = $i
                    break
                }
            }
        }

        if ($groupStart -eq -1) {
            Write-Warning "  Group '$groupName' not found in this target"
            continue
        }

        # Check if file already exists in this group
        $alreadyExists = $false
        for ($i = $groupStart; $i -le $groupEnd; $i++) {
            if ($lines[$i] -match "<FileName>$([regex]::Escape($fileName))</FileName>") {
                $alreadyExists = $true
                break
            }
        }

        if ($alreadyExists) {
            Write-Host "  Already exists: $fileName" -ForegroundColor DarkGray
        } else {
            # Insert the new file entry before </Files> or before <File>
            # Find the last </File> in the group, insert after it
            $insertAfter = -1
            for ($i = $groupEnd; $i -ge $groupStart; $i--) {
                if ($lines[$i] -match '</File>') {
                    $insertAfter = $i
                    break
                }
            }
            if ($insertAfter -eq -1) {
                # No files in group, try inserting after <Files>
                for ($i = $groupStart; $i -le $groupEnd; $i++) {
                    if ($lines[$i] -match '<Files>') {
                        $insertAfter = $i
                        break
                    }
                }
            }

            if ($insertAfter -ne -1) {
                $lines = Add-FileToGroupText -Lines $lines -InsertAfterLine $insertAfter -FileName $fileName -FilePath $filePath
                Write-Host "  Added: $fileName" -ForegroundColor Green
                $modified = $true
            } else {
                Write-Warning "  Cannot find insertion point in group '$groupName'"
            }
        }
    }

    # ---- Write back ----
    if ($modified) {
        $newContent = $lines -join "`r`n"
        # IMPORTANT: Ensure no BOM and no reformatting
        [System.IO.File]::WriteAllText($ProjectPath, $newContent, [System.Text.UTF8Encoding]::new($false))
        Write-Host "  Saved (UTF-8 no BOM)" -ForegroundColor Green
    } else {
        Write-Host "  No changes needed" -ForegroundColor DarkGray
    }
}

# ---- Define files to add per project (group, filename, relpath) ----

$lwipFiles = @(
    , @("USER", "main_at32f403a_lwip_demo.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_lwip_demo.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
    , @("MH2030A_PORT", "at32f403a_lwip_clock.c", "..\dm9051_driver\ports\at32f403a\at32f403a_lwip_clock.c")
    , @("dm9051/lwip_adapter", "ethernetif_at32f403a.c", "..\dm9051_driver\ports\at32f403a\ethernetif_at32f403a.c")
)

$uipFiles = @(
    , @("USER", "main_at32f403a_uip_demo.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_uip_demo.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
    , @("MH2030A_PORT", "at32f403a_uip_clock.c", "..\dm9051_driver\ports\at32f403a\at32f403a_uip_clock.c")
)

$baseFiles = @(
    , @("USER", "main_at32f403a_smoke.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_smoke.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
)

# ---- Execute ----

Fix-At32TargetText -ProjectPath $LwipProjectFile -TargetName "AT32F403A_DM9051_LWIP" -FilesToAdd $lwipFiles
Fix-At32TargetText -ProjectPath $UipProjectFile -TargetName "AT32F403A_DM9051_uIP" -FilesToAdd $uipFiles
Fix-At32TargetText -ProjectPath $BaseProjectFile -TargetName "AT32F403A_DM9051" -FilesToAdd $baseFiles

Write-Host "`nDone." -ForegroundColor Cyan
Write-Host "ACTION REQUIRED: Open projects in Keil uVision, select AT32F403A device in Target Options." -ForegroundColor Yellow
