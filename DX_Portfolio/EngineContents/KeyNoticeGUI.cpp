#include "PreCompile.h"
#include "KeyNoticeGUI.h"

#include <EngineCore/EngineGUI.h>

#include "ContentsEnum.h"
#include "Yoshi.h"
#include "YoshiGameInstance.h"

UKeyNoticeGUI::UKeyNoticeGUI()
{
}

UKeyNoticeGUI::~UKeyNoticeGUI()
{
}

void UKeyNoticeGUI::OnGUI()
{
	PrintGameGuide();
	PrintYellowCoinCount();
}

void UKeyNoticeGUI::PrintGameGuide()
{
	ImGui::Text("<KEY NOTICE>");
	ImGui::Text("StartGame : Space");
	ImGui::Text("Move : Directional key");
	ImGui::Text("Jump : Left Control");
	ImGui::Text("Aim & Throw : Z");
	ImGui::Text("Lick : X");
	ImGui::NewLine();
}

void UKeyNoticeGUI::PrintYellowCoinCount()
{
	std::string YellowCoinCount = "YellowCoin : " + std::to_string(GetWorld()->GetMainPawn<AYoshi>()->GetGameInstance<AYoshiGameInstance>()->YellowCoin);
	YellowCoinCount = UEngineString::AnsiToUTF8(YellowCoinCount);
	ImGui::Text(YellowCoinCount.c_str());
}