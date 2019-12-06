#include "Container.h"



namespace OrigamiEngine {

	Container::Container() {

	}

	Container::~Container() {

	}

	void Container::Draw(const int x, const int y, const int width, const int height) {

	}

	float Container::GetPercentage() {
		return m_Percentage;
	}
	void Container::SetPercentage(const float percentage) {
		m_Percentage = percentage;
	}
}