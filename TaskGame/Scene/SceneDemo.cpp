//#include "SceneDemo.h"
//#include "SceneTitle.h"
//#include"SceneManager.h"
//#include"../UI/game.h"
//#include"../UI/InputState.h"
//#include"../GameManager.h"
//#include<DxLib.h>

//void SceneDemo::FadeInUpdate(const InputState& input)
//{
//	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
//	if (--m_fadeTimer == 0) {
//		m_updateFunc = &SceneDemo::NormalUpdate;
//		m_fadeValue = 0;
//	}
//}
//
//void SceneDemo::NormalUpdate(const InputState& input)
//{
//	//�A�j���[�V�����̏����i�{�^���j
//	m_animation++;
//	if (m_animation > 60)
//	{
//		m_displayCount++;
//		if (m_displayCount >= 5 * 4)
//		{
//			m_animation = 0;
//			m_displayCount = 0;
//		}
//	}
//
//
//	//�u���ցv�{�^���������ꂽ�玟��
//	if (input.IsTrigger(InputType::next))
//	{
//		m_updateFunc = &SceneDemo::FadeOutUpdate;
//	}
//}
//
//void SceneDemo::FadeOutUpdate(const InputState& input)
//{
//	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
//	if (++m_fadeTimer == m_fadeInterval) {
//		m_manager.ChangeScene(new SceneTitle(m_manager));
//		return;
//	}
//}
//
//SceneDemo::SceneDemo(SceneManager& manager) :
//	SceneBase(manager),
//	m_updateFunc(&SceneDemo::FadeInUpdate)
//{
//	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");
//	m_guideFont = CreateFontToHandle(L"HG�ۺ޼��M-PRO", 42, -1, -1);
//	m_demoFont = CreateFontToHandle(L"HG�ۺ޼��M-PRO", 64, -1, -1);
//	m_strEx = static_cast<int>(strlen("A�{�^���������Ă�������"));
//}
//
//SceneDemo::~SceneDemo()
//{
//}
//
//void SceneDemo::Update(const InputState& input)
//{
//	(this->*m_updateFunc)(input);
//}
//
//void SceneDemo::Draw()
//{
//	int posX = (Game::kScreenWindth -
//		GetDrawStringWidthToHandle(L"A�{�^���������Ă�������", m_strEx, m_guideFont)) / 2;
//	int posY = Game::kScreenHeight - 200;
//	int animeNum = (m_displayCount / 5) + 1;
//
//	//�_�ŏ���
//	DrawStringToHandle(posX + 5, posY, L" �{�^���������Ă�������", 0xffffff, m_guideFont);	//�K�C�h�̕\��
// 
//	//�{�^���̏����i�A�j���[�V�����̒ǉ��j
//	my::MyDrawRectRotaGraph(posX - 5, posY + 25,			//�\�����W
//		32 + (16 * animeNum), 16 + (16 * 2),			//�؂��荶��
//		16, 16,							//���A����
//		3.0f, 0.0f,						//�g�嗦�A��]�p�x
//		m_buttonHandle, true);
//}