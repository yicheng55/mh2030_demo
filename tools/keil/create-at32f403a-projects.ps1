param(
    [string]$LwipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_lwip.uvprojx",
    [string]$UipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_uip.uvprojx",
    [string]$BaseProjectFile = "ModuleDemo/DM9051A/USER/DM9051A.uvprojx"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# Files to EXCLUDE from AT32F403A build
$excludeFiles = @(
    'main.c', 'main_uip_mh2030a.c', 'main_uip_mh2030a_smoke.c',
    'main_uip_mh2030a_demo.c', 'main_dm9051_lwip_example.c',
    'mh20xx_it.c', 'system_mh20xx.c', 'startup_mh20xx.s',
    'mh2030a_dm9051_spi.c', 'mh2030a_dm9051_spi_dma.c', 'mh2030a_dm9051_int.c',
    'mh2030a_board.c', 'mh2030a_uip_clock.c', 'dm9051_hal_mh2030a_spi1.c',
    'dm9051_hal_mh2030a_spi1_dma.c', 'dm9051_hal_mh2030a_int.c'
)

# AT32F403A files to INCLUDE per project type
$lwipAddFiles = @(
    , @("USER", "main_at32f403a_lwip_demo.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_lwip_demo.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
    , @("MH2030A_PORT", "at32f403a_lwip_clock.c", "..\dm9051_driver\ports\at32f403a\at32f403a_lwip_clock.c")
    , @("dm9051/lwip_adapter", "ethernetif_at32f403a.c", "..\dm9051_driver\ports\at32f403a\ethernetif_at32f403a.c")
)
$uipAddFiles = @(
    , @("USER", "main_at32f403a_uip_demo.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_uip_demo.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
    , @("MH2030A_PORT", "at32f403a_uip_clock.c", "..\dm9051_driver\ports\at32f403a\at32f403a_uip_clock.c")
)
$baseAddFiles = @(
    , @("USER", "main_at32f403a_smoke.c", "..\dm9051_driver\examples\at32f403a_demo\main_at32f403a_smoke.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_spi1_dma.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1_dma.c")
    , @("MH2030A_PORT", "dm9051_hal_at32f403a_int.c", "..\dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_int.c")
    , @("MH2030A_PORT", "at32f403a_board.c", "..\dm9051_driver\ports\at32f403a\at32f403a_board.c")
)

# Template mapping: source target → new AT32F403A target config
$targetTemplates = @{
    "DM9051A.uvprojx" = @{
        SourceTarget = "DM9051A"
        NewTargetName = "AT32F403A_DM9051"
        NewOutputDir  = "..\OBJ_AT32F403A\"
        NewOutputName = "AT32F403A_DM9051"
        NewDefine     = "USE_STDPERIPH_DRIVER,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        NewIncludePath = "..\USER;..\..\..\Libraries\AT32F403A\inc;;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\examples\at32f403a_demo"
        AddFiles = $baseAddFiles
    }
    "DM9051A_uip.uvprojx" = @{
        SourceTarget = "MH2030A_DM9051_uIP"
        NewTargetName = "AT32F403A_DM9051_uIP"
        NewOutputDir  = "..\OBJ_AT32F403A_UIP\"
        NewOutputName = "AT32F403A_DM9051_uIP"
        NewDefine     = "USE_STDPERIPH_DRIVER,AT32F403A_UIP_PORT,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        NewIncludePath = "..\USER;..\..\..\Libraries\AT32F403A\inc;;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\adapters\uip;..\dm9051_driver\examples\at32f403a_demo;..\..\..\middlewares\3rd_party\uip\inc;..\..\..\middlewares\3rd_party\uip\port\at32f415_dm9051;..\..\..\apps\uip_dm9051_example_e1\example_uip\inc;..\..\..\apps\uip_dm9051_example_e1\uip_conf_inc;..\..\..\apps\uip_dm9051_example_e1\uip_app_src;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\Eth_app\dhcpc;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\Eth_app\resolv;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\webserver\inc"
        AddFiles = $uipAddFiles
    }
    "DM9051A_lwip.uvprojx" = @{
        SourceTarget = "MH2030A_DM9051_LWIP"
        NewTargetName = "AT32F403A_DM9051_LWIP"
        NewOutputDir  = "..\OBJ_AT32F403A_LWIP\"
        NewOutputName = "AT32F403A_DM9051_LWIP"
        NewDefine     = "USE_STDPERIPH_DRIVER,AT32F403A_LWIP_PORT,NO_SYS=1,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        NewIncludePath = "..\USER;..\..\..\Libraries\AT32F403A\inc;;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\adapters\lwip;..\dm9051_driver\examples\at32f403a_demo;..\..\..\middlewares\3rd_party\lwip-2.1.2\src\include;..\..\..\middlewares\3rd_party\lwip-2.1.2\port;..\..\..\apps\lwip_web2403v2_freelw"
        AddFiles = $lwipAddFiles
    }
}

function Set-IncludeInBuild {
    param([string[]]$Lines, [int]$TargetStart, [int]$TargetEnd, [string]$FileName, [int]$Value)
    for ($i = $TargetStart; $i -le $TargetEnd; $i++) {
        if ($Lines[$i] -match "<FileName>$([regex]::Escape($FileName))</FileName>") {
            for ($j = $i; $j -le $TargetEnd -and $j -lt $Lines.Length; $j++) {
                if ($Lines[$j] -match '<IncludeInBuild>') {
                    $Lines[$j] = $Lines[$j] -replace '<IncludeInBuild>[^<]*</IncludeInBuild>', "<IncludeInBuild>$Value</IncludeInBuild>"
                    Write-Host "    Set $FileName IncludeInBuild=$Value" -ForegroundColor DarkGray
                    return ,$Lines
                }
                if ($Lines[$j] -match '<IncludeInBuild\s*/?>') {
                    $Lines[$j] = "                <IncludeInBuild>$Value</IncludeInBuild>"
                    Write-Host "    Set $FileName IncludeInBuild=$Value" -ForegroundColor DarkGray
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
                    Write-Host "    Set $FileName IncludeInBuild=$Value (added)" -ForegroundColor DarkGray
                    return ,$Lines
                }
            }
            return ,$Lines
        }
    }
    return ,$Lines
}

function Add-FileToGroupText {
    param([string[]]$Lines, [int]$InsertAfterLine, [string]$FileName, [string]$FilePath)
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
            foreach ($nl in $newLines) { $result.Add($nl) }
        }
    }
    return $result.ToArray()
}

function Remove-TargetByName {
    param([string[]]$Lines, [string]$TargetName)

    $start = -1; $end = -1; $depth = 0; $inTarget = $false

    for ($i = 0; $i -lt $Lines.Length; $i++) {
        if (-not $inTarget) {
            if ($Lines[$i] -match "<TargetName>$([regex]::Escape($TargetName))</TargetName>") {
                $inTarget = $true
                for ($j = $i; $j -ge 0; $j--) {
                    if ($Lines[$j] -match '<Target>') { $start = $j; break }
                }
            }
        } else {
            if ($Lines[$i] -match '</Target>') { $end = $i; break }
        }
    }
    if ($start -eq -1) { return ,$Lines }

    Write-Host "  Removing target '$TargetName' (lines $start-$end)" -ForegroundColor DarkGray
    $Lines = $Lines[0..($start-1)] + $Lines[($end+1)..($Lines.Length-1)]
    return ,$Lines
}

# ======== MAIN ========

foreach ($projectFile in @($BaseProjectFile, $UipProjectFile, $LwipProjectFile)) {
    $projName = Split-Path -Leaf $projectFile
    $template = $targetTemplates[$projName]
    if ($null -eq $template) { continue }

    Write-Host "`n=== Processing $projName ===" -ForegroundColor Cyan

    # Read original file
    $originalContent = Get-Content -LiteralPath $projectFile -Raw
    $lines = @($originalContent -split "`r`n|`n")

    # ----- Step 1: Find source target range and clone it -----
    $sourceName = $template.SourceTarget
    $newName = $template.NewTargetName
    $sourceStart = -1; $sourceEnd = -1; $inTarget = $false

    for ($i = 0; $i -lt $Lines.Length; $i++) {
        if (-not $inTarget) {
            if ($Lines[$i] -match "<TargetName>$([regex]::Escape($sourceName))</TargetName>") {
                $inTarget = $true
                for ($j = $i; $j -ge 0; $j--) {
                    if ($Lines[$j] -match '<Target>') { $sourceStart = $j; break }
                }
            }
        } else {
            if ($Lines[$i] -match '</Target>') { $sourceEnd = $i; break }
        }
    }

    if ($sourceStart -eq -1) {
        Write-Warning "  Source target '$sourceName' not found"
        continue
    }

    Write-Host "  Cloning target '$sourceName' (lines $sourceStart-$sourceEnd)" -ForegroundColor DarkGray
    $cloneLines = $Lines[$sourceStart..$sourceEnd]

    # Rename the cloned target
    for ($i = 0; $i -lt $cloneLines.Length; $i++) {
        if ($cloneLines[$i] -match "<TargetName>$([regex]::Escape($sourceName))</TargetName>") {
            $cloneLines[$i] = $cloneLines[$i] -replace [regex]::Escape($sourceName), $newName
        }
        if ($cloneLines[$i] -match "<OutputName>" -and $cloneLines[$i] -match [regex]::Escape($sourceName)) {
            $cloneLines[$i] = $cloneLines[$i] -replace [regex]::Escape($sourceName), $template.NewOutputName
        }
    }

    # Fix OutputDirectory
    for ($i = 0; $i -lt $cloneLines.Length; $i++) {
        if ($cloneLines[$i] -match '<OutputDirectory>') {
            $cloneLines[$i] = "          <OutputDirectory>$($template.NewOutputDir)</OutputDirectory>"
        }
    }

    # Fix Cads/Define
    $inCads = $false; $inVarious = $false
    for ($i = 0; $i -lt $cloneLines.Length; $i++) {
        if ($cloneLines[$i] -match '<Cads>') { $inCads = $true }
        if ($inCads -and $cloneLines[$i] -match '<VariousControls>') { $inVarious = $true }
        if ($inVarious -and $cloneLines[$i] -match '<Define>') {
            $cloneLines[$i] = $cloneLines[$i] -replace '<Define>[^<]*</Define>', "<Define>$($template.NewDefine)</Define>"
            $inVarious = $false; $inCads = $false
        }
        if ($inVarious -and $cloneLines[$i] -match '<IncludePath>') {
            $cloneLines[$i] = $cloneLines[$i] -replace '<IncludePath>[^<]*</IncludePath>', "<IncludePath>$($template.NewIncludePath)</IncludePath>"
        }
    }

    # Save original file (unmodified)
    $origContent = $lines -join "`r`n"
    [System.IO.File]::WriteAllText($projectFile, $origContent, [System.Text.UTF8Encoding]::new($false))
    Write-Host "  Original file untouched" -ForegroundColor Green

    # ----- Step 2: Create new file = original + cloned target -----
    $newFilePath = $projectFile -replace '\.uvprojx$', '_at32f403a.uvprojx'
    Write-Host "  Creating: $newFilePath" -ForegroundColor Cyan

    # Insert cloned target after last </Target> in original
    $lastTargetEnd = 0
    for ($i = 0; $i -lt $lines.Length; $i++) {
        if ($lines[$i] -match '</Target>') { $lastTargetEnd = $i }
    }
    $newLines = $lines[0..$lastTargetEnd] + $cloneLines + $lines[($lastTargetEnd+1)..($lines.Length-1)]

    # ----- Step 3: Remove all MH2030A targets from new file -----
    $mh2030Targets = @()
    $inTarget = $false
    for ($i = 0; $i -lt $newLines.Length; $i++) {
        if (-not $inTarget) {
            if ($newLines[$i] -match '<TargetName>(MH2030A_[^<]+)</TargetName>') {
                $mh2030Targets += $matches[1]
            }
        }
    }
    # Also remove DM9051A and DM9051A_SPI_DMA targets (they are MH2030A targets)
    for ($i = 0; $i -lt $newLines.Length; $i++) {
        if (-not $inTarget) {
            if ($newLines[$i] -match '<TargetName>(DM9051A[^<]*)</TargetName>' -and $newLines[$i] -notmatch 'AT32F403A') {
                $tn = $matches[1]
                if ($tn -ne $newName) { $mh2030Targets += $tn }
            }
        }
    }
    # Remove duplicates
    $mh2030Targets = $mh2030Targets | Select-Object -Unique

    foreach ($tn in $mh2030Targets) {
        $newLines = Remove-TargetByName -Lines $newLines -TargetName $tn
    }

    # ----- Step 4: Apply fixes to AT32F403A target in new file -----
    # Find the AT32F403A target range
    $targetStart = -1; $targetEnd = -1; $inTarget = $false
    for ($i = 0; $i -lt $newLines.Length; $i++) {
        if (-not $inTarget) {
            if ($newLines[$i] -match "<TargetName>$([regex]::Escape($newName))</TargetName>") {
                $inTarget = $true
                for ($j = $i; $j -ge 0; $j--) {
                    if ($newLines[$j] -match '<Target>') { $targetStart = $j; break }
                }
            }
        } else {
            if ($newLines[$i] -match '</Target>') { $targetEnd = $i; break }
        }
    }

    Write-Host "  AT32F403A target at lines $targetStart-$targetEnd" -ForegroundColor DarkGray

    if ($targetStart -ne -1) {
        # Fix Device, Vendor, Cpu, PackID, PackURL, FlashDriverDll, RegisterFile, SFDFile
        for ($i = $targetStart; $i -le $targetEnd; $i++) {
            if ($newLines[$i] -match '<Device>')     { $newLines[$i] = '          <Device></Device>' }
            if ($newLines[$i] -match '<Vendor>')     { $newLines[$i] = '          <Vendor></Vendor>' }
            if ($newLines[$i] -match '<Cpu>')        { $newLines[$i] = '          <Cpu>CPUTYPE("Cortex-M4") ESEL ELITTLE</Cpu>' }
            if ($newLines[$i] -match '<PackID>')     { $newLines[$i] = '          <PackID></PackID>' }
            if ($newLines[$i] -match '<PackURL>')    { $newLines[$i] = '          <PackURL></PackURL>' }
            if ($newLines[$i] -match '<FlashDriverDll>') { $newLines[$i] = '          <FlashDriverDll></FlashDriverDll>' }
            if ($newLines[$i] -match '<RegisterFile>')   { $newLines[$i] = '          <RegisterFile></RegisterFile>' }
            if ($newLines[$i] -match '<SFDFile>')        { $newLines[$i] = '          <SFDFile></SFDFile>' }
            if ($newLines[$i] -match '<AdsCpuType>') {
                $newLines[$i] = $newLines[$i] -replace '"Cortex-M0"', '"Cortex-M4"'
            }
        }

        # Set IncludeInBuild for MH2030A files → 0, delay.c → 1
        foreach ($fname in $excludeFiles) {
            $newLines = Set-IncludeInBuild -Lines $newLines -TargetStart $targetStart -TargetEnd $targetEnd -FileName $fname -Value 0
        }
        $newLines = Set-IncludeInBuild -Lines $newLines -TargetStart $targetStart -TargetEnd $targetEnd -FileName "delay.c" -Value 1

        # Add AT32F403A files
        foreach ($entry in $template.AddFiles) {
            $gname = $entry[0]; $fname = $entry[1]; $fpath = $entry[2]
            $gStart = -1; $gEnd = -1; $inGroup = $false
            for ($i = $targetStart; $i -le $targetEnd; $i++) {
                if (-not $inGroup) {
                    if ($newLines[$i] -match "<GroupName>$([regex]::Escape($gname))</GroupName>") {
                        $inGroup = $true
                        for ($j = $i; $j -ge $targetStart; $j--) {
                            if ($newLines[$j] -match '<Group>') { $gStart = $j; break }
                        }
                    }
                } else {
                    if ($newLines[$i] -match '</Group>') { $gEnd = $i; break }
                }
            }
            if ($gStart -eq -1) { Write-Warning "    Group '$gname' not found"; continue }
            # Check if file already exists
            $exists = $false
            for ($i = $gStart; $i -le $gEnd; $i++) {
                if ($newLines[$i] -match "<FileName>$([regex]::Escape($fname))</FileName>") { $exists = $true; break }
            }
            if ($exists) { Write-Host "    Already exists: $fname" -ForegroundColor DarkGray; continue }
            # Find insertion point
            $insertAfter = -1
            for ($i = $gEnd; $i -ge $gStart; $i--) {
                if ($newLines[$i] -match '</File>') { $insertAfter = $i; break }
            }
            if ($insertAfter -eq -1) {
                for ($i = $gStart; $i -le $gEnd; $i++) {
                    if ($newLines[$i] -match '<Files>') { $insertAfter = $i; break }
                }
            }
            if ($insertAfter -ne -1) {
                $newLines = Add-FileToGroupText -Lines $newLines -InsertAfterLine $insertAfter -FileName $fname -FilePath $fpath
                Write-Host "    Added: $fname" -ForegroundColor Green
            }
        }
    }

    # Save new project file
    $newContent = $newLines -join "`r`n"
    [System.IO.File]::WriteAllText($newFilePath, $newContent, [System.Text.UTF8Encoding]::new($false))
    Write-Host "  Saved: $newFilePath" -ForegroundColor Green
    Write-Host "  Open in Keil uVision, select AT32F403A device in Target -> Options -> Device" -ForegroundColor Yellow
}

Write-Host "`nDone." -ForegroundColor Cyan
Write-Host "New files created:" -ForegroundColor Cyan
Write-Host "  ModuleDemo/DM9051A/USER/DM9051A_at32f403a.uvprojx" -ForegroundColor White
Write-Host "  ModuleDemo/DM9051A/USER/DM9051A_at32f403a_uip.uvprojx" -ForegroundColor White
Write-Host "  ModuleDemo/DM9051A/USER/DM9051A_at32f403a_lwip.uvprojx" -ForegroundColor White
Write-Host "Original files unchanged." -ForegroundColor Cyan
