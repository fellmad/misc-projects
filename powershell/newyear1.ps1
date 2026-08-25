# https://gist.github.com/mattle/b516f9f51640738ae468013dec5a7450
Add-Type -AssemblyName System.speech
$voice = New-Object System.Speech.Synthesis.SpeechSynthesizer
$now = Get-Date
$first = Get-Date ('1/1/' + (($now).Year + 1))
Clear-Host
while ($now -lt $first) {
    $span = New-Timespan -start $now -end $first
    $format = "$($span.Days) Days $($span.Hours) Hours $($span.Minutes) Minutes $($span.Seconds) Seconds".PadRight(58)
    [Console]::SetCursorPosition(0, 0)
    [Console]::Write("New Year's Countdown: $format")
    Start-Sleep 1
    $now = Get-Date
}
Clear-Host
Write-Output "🥳 Happy New Year!!!"
$voice.Speak("Happy New Year!")