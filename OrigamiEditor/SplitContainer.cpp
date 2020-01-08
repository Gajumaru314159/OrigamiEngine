#include <DxLib.h>

#include "SplitContainer.h"

#include "Input.h"
#include "WindowManager.h"



namespace OrigamiEngine {

	SplitContainer::~SplitContainer() {
	}

	void SplitContainer::SetIsVertical(bool isVertival) {
		m_IsVertical = isVertival;
	}

	void SplitContainer::Draw(const S32 x, const S32 y, const S32 width, const S32 height) {
		const S32 BORDER_WEIGHT = 4;
		const S32 MIN_WIDTH = 120;
		const S32 MIN_HEIGHT = 100;

		S32 mouseX, mouseY;
		S32  containerIndex = 0;
		GetMousePoint(&mouseX, &mouseY);

		if (m_IsVertical) {
			//��
			//��
			S32 top = y;
			for (size_t i = 0; i < m_Containers.size(); i++) {
				auto& container = m_Containers.at(i);

				// �R���e�i�̉����W���v�Z
				S32 bottom = y + S32(height * container->GetPercentage());

				// �{�[�_�̃h���b�O����
				if (i < m_Containers.size() - 1) {
					if (Input::GetMouseHover(x, bottom, x + width, bottom + BORDER_WEIGHT)) {
						WindowManager::GetInstance().SetMouseCursor(WindowManager::SIZENS);
						if (Input::GetMouseButtonDown(0)) {
							m_DragIndex = containerIndex;
						}
					}

					if (m_DragIndex == containerIndex) {
						auto& nextContainer = m_Containers.at(i + 1);
						S32 nextBorder = y + S32(height * nextContainer->GetPercentage());

						S32 draggedPoS32 = mouseY - BORDER_WEIGHT / 2;
						// �h���b�O�ʒu���͂ݏo���Ȃ��悤�ɐ��K��
						draggedPoS32 = max(min(draggedPoS32, nextBorder - MIN_HEIGHT), top + MIN_HEIGHT);
						container->SetPercentage((float)(draggedPoS32 - y) / height);
					}
				}


				if (i == 0) {
					container->Draw(x, top, width, bottom - top);
				}
				else {
					container->Draw(x, top + BORDER_WEIGHT, width, bottom - (top + BORDER_WEIGHT));
				}

				top = bottom;
				containerIndex++;
			}
		}
		else {
			//����
			S32 left = x;
			for (size_t i = 0; i < m_Containers.size(); i++) {
				auto& container = m_Containers.at(i);

				// �R���e�i�̉E���W���v�Z
				S32 right = x + S32(width * container->GetPercentage());

				// �{�[�_�̃h���b�O����
				if (i < m_Containers.size() - 1) {
					// �N���b�N���ꂽ���E�̃C���f�b�N�X���L�^
					if (Input::GetMouseHover(right, y, right + BORDER_WEIGHT, y + height)) {
						WindowManager::GetInstance().SetMouseCursor(WindowManager::SIZEWE);
						if (Input::GetMouseButtonDown(0)) {
							m_DragIndex = containerIndex;
						}
					}

					if (m_DragIndex == containerIndex) {
						auto& nextContainer = m_Containers.at(i + 1);
						S32 nextBorder = x + S32(width * nextContainer->GetPercentage());

						// �h���b�O�ʒu���͂ݏo���Ȃ��悤�ɐ��K��
						S32 draggedPoS32 = mouseX - BORDER_WEIGHT / 2;
						draggedPoS32 = max(min(draggedPoS32, nextBorder - MIN_WIDTH), left + MIN_WIDTH);
						container->SetPercentage((float)(draggedPoS32 - x) / width);
					}
				}


				// �`�敔
				if (i == 0) {
					container->Draw(left, y, right - left, height);
				}
				else {
					container->Draw(left + BORDER_WEIGHT, y, right - (left + BORDER_WEIGHT), height);
				}

				left = right;
				containerIndex++;
			}
		}

		// �h���b�O�̏I��
		if (!Input::GetMouseButton(0)) {
			m_DragIndex = -1;
		}
	}


	bool SplitContainer::AddTab(ITab* tab, const U32 index) {
		for (U32 i = 0; i < m_Containers.size(); i++) {
			auto& container = m_Containers.at(i);
			bool result=container->AddTab(tab);
			if (result) {
				return true;
			}
		}
		return false;
	}

	void SplitContainer::AddContainer(std::unique_ptr<Container>&& container, float endPercentage) {
		// �͈͊O�̏ꍇ�͕␳���ď����𑱍s
		endPercentage = max(min(endPercentage, 1.0f), 0.0f);
		if (m_Containers.empty())endPercentage = 1.0f;

		S32 index = 0;
		for (U32 i = 0; i < m_Containers.size(); i++) {
			if (endPercentage < m_Containers.at(i)->GetPercentage())break;
			index++;
		}

		container->SetPercentage(endPercentage);
		m_Containers.insert(m_Containers.begin() + index, std::move(container));
	}

}