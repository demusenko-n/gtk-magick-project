#include "NumberEntry.h"

void NumberEntry::on_changed()
{
	const auto& text = get_text();

	std::string filtered_text;
	filtered_text.reserve(text.size());

	for (const auto& ch : text)
	{
		if (std::isdigit(ch))
		{
			filtered_text += ch;
		}
	}

	const auto size_diff = text.size() - filtered_text.size();
	if (size_diff > 0)
	{
		const auto position = get_position();
		set_text(filtered_text);
		// this produces a warning, but I didn't find good way to work around it
		set_position(position - size_diff);
	}
}