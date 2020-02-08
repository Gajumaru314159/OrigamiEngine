#include "Container.h"



namespace OrigamiEngine {
	float Container::GetPercentage() {
		return m_Percentage;
	}
	void Container::SetPercentage(const float percentage) {
		m_Percentage = percentage;
	}
}