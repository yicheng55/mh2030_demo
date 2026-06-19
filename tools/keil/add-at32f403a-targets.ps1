param(
    [string]$LwipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_lwip.uvprojx",
    [string]$UipProjectFile = "ModuleDemo/DM9051A/USER/DM9051A_uip.uvprojx",
    [string]$BaseProjectFile = "ModuleDemo/DM9051A/USER/DM9051A.uvprojx",
    [string]$At32BspInclude = "",
    [switch]$DryRun
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Add-At32Target {
    param(
        [string]$ProjectPath,
        [string]$SourceTargetName,
        [string]$NewTargetName,
        [string]$NewOutputDir,
        [string]$NewOutputName,
        [string]$NewDefine,
        [string]$NewIncludePath
    )

    if (-not (Test-Path -LiteralPath $ProjectPath)) {
        Write-Warning "Project not found: $ProjectPath — skipping"
        return
    }

    Write-Host "Processing $ProjectPath ..." -ForegroundColor Cyan

    [xml]$xml = Get-Content -LiteralPath $ProjectPath
    $ns = New-Object System.Xml.XmlNamespaceManager($xml.NameTable)
    $ns.AddNamespace('ns', $xml.DocumentElement.NamespaceURI)

    $targetsNode = $xml.SelectSingleNode('//ns:Targets', $ns)
    $sourceTarget = $xml.SelectSingleNode("//ns:Target[ns:TargetName='$SourceTargetName']", $ns)

    if ($null -eq $sourceTarget) {
        Write-Warning "Source target '$SourceTargetName' not found in $ProjectPath — skipping"
        return
    }

    $existing = $xml.SelectSingleNode("//ns:Target[ns:TargetName='$NewTargetName']", $ns)
    if ($null -ne $existing) {
        Write-Host "  Target '$NewTargetName' already exists — skipping" -ForegroundColor Yellow
        return
    }

    $newTarget = $sourceTarget.CloneNode($true)

    $newTarget.SelectSingleNode('ns:TargetName', $ns).InnerText = $NewTargetName

    $common = $newTarget.SelectSingleNode('ns:TargetOption/ns:TargetCommonOption', $ns)
    if ($common) {
        $common.SelectSingleNode('ns:OutputDirectory', $ns).InnerText = $NewOutputDir
        $common.SelectSingleNode('ns:OutputName', $ns).InnerText = $NewOutputName
    }

    $cadsDefines = $newTarget.SelectSingleNode('ns:TargetOption/ns:TargetArmAds/ns:Cads/ns:VariousControls/ns:Define', $ns)
    if ($cadsDefines) {
        $cadsDefines.InnerText = $NewDefine
    }

    $cadsIncludes = $newTarget.SelectSingleNode('ns:TargetOption/ns:TargetArmAds/ns:Cads/ns:VariousControls/ns:IncludePath', $ns)
    if ($cadsIncludes -and $NewIncludePath) {
        $cadsIncludes.InnerText = $NewIncludePath
    }

    $prevTarget = $targetsNode.SelectSingleNode("ns:Target[ns:TargetName='$SourceTargetName']", $ns)
    if ($null -eq $prevTarget) {
        $targetsNode.AppendChild($newTarget) | Out-Null
    } else {
        $targetsNode.InsertAfter($newTarget, $prevTarget) | Out-Null
    }

    if ($DryRun) {
        Write-Host "  [DRY RUN] Would save changes to $ProjectPath" -ForegroundColor Yellow
    } else {
        $xml.Save($ProjectPath)
        Write-Host "  Saved $ProjectPath" -ForegroundColor Green
    }
}

$lwipDefines = "USE_STDPERIPH_DRIVER,AT32F403A_LWIP_PORT,NO_SYS=1,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
$lwipIncludes = "..\USER;..\..\..\Libraries\AT32F403A\inc;$At32BspInclude;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\adapters\lwip;..\dm9051_driver\examples\at32f403a_demo;..\..\..\middlewares\3rd_party\lwip-2.1.2\src\include;..\..\..\middlewares\3rd_party\lwip-2.1.2\port;..\..\..\apps\lwip_web2403v2_freelw"

Add-At32Target -ProjectPath $LwipProjectFile `
    -SourceTargetName "MH2030A_DM9051_LWIP" `
    -NewTargetName "AT32F403A_DM9051_LWIP" `
    -NewOutputDir "..\OBJ_AT32F403A_LWIP\" `
    -NewOutputName "AT32F403A_DM9051_LWIP" `
    -NewDefine $lwipDefines `
    -NewIncludePath $lwipIncludes

$uipDefines = "USE_STDPERIPH_DRIVER,AT32F403A_UIP_PORT,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1"
$uipIncludes = "..\USER;..\..\..\Libraries\AT32F403A\inc;$At32BspInclude;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\adapters\uip;..\dm9051_driver\examples\at32f403a_demo;..\..\..\middlewares\3rd_party\uip\inc;..\..\..\middlewares\3rd_party\uip\port\at32f415_dm9051;..\..\..\apps\uip_dm9051_example_e1\example_uip\inc;..\..\..\apps\uip_dm9051_example_e1\uip_conf_inc;..\..\..\apps\uip_dm9051_example_e1\uip_app_src;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\Eth_app\dhcpc;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\Eth_app\resolv;..\..\..\apps\uip_dm9051_example_e1\uip_app_src\webserver\inc"

Add-At32Target -ProjectPath $UipProjectFile `
    -SourceTargetName "MH2030A_DM9051_uIP" `
    -NewTargetName "AT32F403A_DM9051_uIP" `
    -NewOutputDir "..\OBJ_AT32F403A_UIP\" `
    -NewOutputName "AT32F403A_DM9051_uIP" `
    -NewDefine $uipDefines `
    -NewIncludePath $uipIncludes

Add-At32Target -ProjectPath $BaseProjectFile `
    -SourceTargetName "DM9051A" `
    -NewTargetName "AT32F403A_DM9051" `
    -NewOutputDir "..\OBJ_AT32F403A\" `
    -NewOutputName "AT32F403A_DM9051" `
    -NewDefine "USE_STDPERIPH_DRIVER,DM9051_AT32F403A_DIAG=1,DM9051_TX_WAIT_DONE=1,DM9051_AT32F403A_USE_DMA=1,DM9051_AT32F403A_USE_IRQ=1" `
    -NewIncludePath "..\USER;..\..\..\Libraries\AT32F403A\inc;$At32BspInclude;..\dm9051_driver\core\inc;..\dm9051_driver\hal\inc;..\dm9051_driver\ports\at32f403a;..\dm9051_driver\examples\at32f403a_demo"

Write-Host "`nDone. After running, open the project in Keil uVision and:" -ForegroundColor Cyan
Write-Host "  1. Select the new AT32F403A_* target from the dropdown" -ForegroundColor Cyan
Write-Host "  2. Go to Project -> Options for Target -> Device tab" -ForegroundColor Cyan
Write-Host "  3. Select the correct AT32F403A device" -ForegroundColor Cyan
Write-Host "  4. Verify C/C++ tab -> Define and Include Paths are correct" -ForegroundColor Cyan
Write-Host "  5. Adjust file inclusion per target in the Project pane" -ForegroundColor Cyan
Write-Host "`nRequired: Install AT32F403A device pack in Keil MDK first." -ForegroundColor Yellow
