param(
    [string]$ProjectFile = "ModuleDemo/DM9051A/USER/DM9051A.uvprojx"
)

# Which targets are expected in which project file
$projectTargets = @{
    "DM9051A.uvprojx" = @("DM9051A", "DM9051A_SPI_DMA", "MH2030A_DM9051_uIP", "MH2030A_DM9051_uIP_dma", "MH2030A_DM9051_uIP_int", "AT32F403A_DM9051")
    "DM9051A_uip.uvprojx" = @("MH2030A_DM9051_uIP", "AT32F403A_DM9051_uIP")
    "DM9051A_lwip.uvprojx" = @("MH2030A_DM9051_uIP", "MH2030A_DM9051_LWIP", "AT32F403A_DM9051_LWIP")
}

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $ProjectFile)) {
    Write-Error "Project file not found: $ProjectFile"
    exit 2
}

[xml]$xml = Get-Content -LiteralPath $ProjectFile
$targets = $xml.Project.Targets.Target

$expected = @{
    "DM9051A" = @{
        OutputDir = "..\OBJ\"
        Define = "USE_STDPERIPH_DRIVER"
        Files = @{
            "main.c" = 1
            "main_uip_mh2030a.c" = 0
            "mh2030a_dm9051_spi.c" = 1
            "mh2030a_dm9051_spi_dma.c" = 1
            "mh2030a_dm9051_int.c" = 1
        }
    }
    "DM9051A_SPI_DMA" = @{
        OutputDir = "..\OBJ\"
        Define = "USE_STDPERIPH_DRIVER"
        Files = @{
            "main.c" = 1
            "main_uip_mh2030a.c" = 0
            "mh2030a_dm9051_spi.c" = 0
            "mh2030a_dm9051_spi_dma.c" = 1
            "mh2030a_dm9051_int.c" = 1
        }
    }
    "MH2030A_DM9051_uIP" = @{
        OutputDir = "..\OBJ_UIP\"
        Define = "USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT"
        Files = @{
            "main.c" = 0
            "main_uip_mh2030a.c" = 1
            "mh2030a_dm9051_spi.c" = 1
            "mh2030a_dm9051_spi_dma.c" = 0
            "mh2030a_dm9051_int.c" = 1
        }
    }
    "MH2030A_DM9051_uIP_dma" = @{
        OutputDir = "..\OBJ_UIP\"
        Define = "USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT,MH2030A_DM9051_SPI_DMA"
        Files = @{
            "main.c" = 0
            "main_uip_mh2030a.c" = 1
            "mh2030a_dm9051_spi.c" = 0
            "mh2030a_dm9051_spi_dma.c" = 1
            "mh2030a_dm9051_int.c" = 1
        }
    }
    "MH2030A_DM9051_uIP_int" = @{
        OutputDir = "..\OBJ_UIP_INT\"
        Define = "USE_STDPERIPH_DRIVER,MH2030A_UIP_PORT,DMPLUG_INT"
        Files = @{
            "main.c" = 0
            "main_uip_mh2030a.c" = 1
            "mh2030a_dm9051_spi.c" = 1
            "mh2030a_dm9051_spi_dma.c" = 0
            "mh2030a_dm9051_int.c" = 1
        }
    }
    "AT32F403A_DM9051" = @{
        OutputDir = "..\OBJ_AT32F403A\"
        Define = "USE_STDPERIPH_DRIVER,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        Files = @{
            "main.c" = 0
            "main_uip_mh2030a.c" = 0
            "mh2030a_dm9051_spi.c" = 0
            "mh2030a_dm9051_spi_dma.c" = 0
            "mh2030a_dm9051_int.c" = 0
            "mh20xx_it.c" = 0
            "system_mh20xx.c" = 0
            "startup_mh20xx.s" = 0
            "delay.c" = 1
            "dm9051_hal_at32f403a_spi1.c" = 1
            "dm9051_hal_at32f403a_spi1_dma.c" = 1
            "dm9051_hal_at32f403a_int.c" = 1
            "at32f403a_board.c" = 1
            "main_at32f403a_smoke.c" = 1
        }
    }
    "AT32F403A_DM9051_uIP" = @{
        OutputDir = "..\OBJ_AT32F403A_UIP\"
        Define = "USE_STDPERIPH_DRIVER,AT32F403A_UIP_PORT,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        Files = @{
            "main_uip_mh2030a_smoke.c" = 0
            "main_uip_mh2030a_demo.c" = 0
            "mh20xx_it.c" = 0
            "system_mh20xx.c" = 0
            "startup_mh20xx.s" = 0
            "delay.c" = 1
            "dm9051_hal_at32f403a_spi1.c" = 1
            "dm9051_hal_at32f403a_spi1_dma.c" = 1
            "dm9051_hal_at32f403a_int.c" = 1
            "at32f403a_board.c" = 1
            "at32f403a_uip_clock.c" = 1
            "main_at32f403a_uip_demo.c" = 1
        }
    }
    "AT32F403A_DM9051_LWIP" = @{
        OutputDir = "..\OBJ_AT32F403A_LWIP\"
        Define = "USE_STDPERIPH_DRIVER,AT32F403A_LWIP_PORT,NO_SYS=1,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
        Files = @{
            "main_uip_mh2030a_smoke.c" = 0
            "main_uip_mh2030a_demo.c" = 0
            "main_dm9051_lwip_example.c" = 0
            "mh20xx_it.c" = 0
            "system_mh20xx.c" = 0
            "startup_mh20xx.s" = 0
            "delay.c" = 1
            "dm9051_hal_at32f403a_spi1.c" = 1
            "dm9051_hal_at32f403a_spi1_dma.c" = 1
            "dm9051_hal_at32f403a_int.c" = 1
            "at32f403a_board.c" = 1
            "at32f403a_lwip_clock.c" = 1
            "ethernetif_at32f403a.c" = 1
            "main_at32f403a_lwip_demo.c" = 1
        }
    }
}

function Get-IncludeInBuildValue {
    param([object]$fileNode)

    $includeNode = $fileNode.SelectSingleNode('FileOption/CommonProperty/IncludeInBuild')
    if ($null -eq $includeNode) {
        return 1
    }

    $raw = [string]$includeNode.InnerText
    if ([string]::IsNullOrWhiteSpace($raw)) {
        return 1
    }

    return [int]$raw
}

$failures = New-Object System.Collections.Generic.List[string]

$projectName = Split-Path -Leaf $ProjectFile
$validTargets = $projectTargets[$projectName]
if ($null -eq $validTargets) {
    Write-Error "Unknown project: $projectName. Add to `$projectTargets."
    exit 2
}

foreach ($targetName in $validTargets) {
    $t = $targets | Where-Object { $_.TargetName -eq $targetName }
    if ($null -eq $t) {
        $failures.Add("Missing target: $targetName")
        continue
    }

    $exp = $expected[$targetName]
    if ($null -eq $exp) {
        Write-Host "  [SKIP] $targetName — no validation expectations defined" -ForegroundColor DarkGray
        continue
    }
    $actualOutputDir = [string]$t.TargetOption.TargetCommonOption.OutputDirectory
    $actualDefine = [string]$t.TargetOption.TargetArmAds.Cads.VariousControls.Define

    if ($actualOutputDir -ne $exp.OutputDir) {
        $failures.Add("[$targetName] OutputDir mismatch. expected='$($exp.OutputDir)' actual='$actualOutputDir'")
    }

    if ($actualDefine -ne $exp.Define) {
        $failures.Add("[$targetName] Define mismatch. expected='$($exp.Define)' actual='$actualDefine'")
    }

    $fileNodes = @{}
    foreach ($g in $t.Groups.Group) {
        foreach ($f in $g.Files.File) {
            $fileNodes[[string]$f.FileName] = $f
        }
    }

    foreach ($fileName in $exp.Files.Keys) {
        $expectedInc = [int]$exp.Files[$fileName]
        if ($expectedInc -eq -1) {
            continue
        }

        if (-not $fileNodes.ContainsKey($fileName)) {
            $failures.Add("[$targetName] Missing file node: $fileName")
            continue
        }

        $actualInc = Get-IncludeInBuildValue -fileNode $fileNodes[$fileName]
        if ($actualInc -ne $expectedInc) {
            $failures.Add("[$targetName] IncludeInBuild mismatch for $fileName. expected=$expectedInc actual=$actualInc")
        }
    }
}

if ($failures.Count -gt 0) {
    Write-Host "DM9051 target validation FAILED:" -ForegroundColor Red
    $failures | ForEach-Object { Write-Host "- $_" -ForegroundColor Red }
    exit 1
}

Write-Host "DM9051 target validation PASSED." -ForegroundColor Green
exit 0
