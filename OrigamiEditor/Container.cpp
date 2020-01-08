#include "Container.h"



namespace OrigamiEngine {

	Container::Container() {

	}

	Container::~Container() {

	}

	float Container::GetPercentage() {
		return m_Percentage;
	}
	void Container::SetPercentage(const float percentage) {
		m_Percentage = percentage;
	}
}