#pragma once
#include <Re\Common\Control\Control.h>
#include <unordered_map>

namespace Game
{

	/// manages input from player
	/// holds whole input settings in one place
	class InputController : public Res::ISerialisable
	{
	public:

		void setKey(const string& code, Control::MultiKey* key)
		{
			keys[code] = std::unique_ptr<Control::MultiKey>(key);
		}
		Control::MultiKey* getKey(const string& code)
		{
			return keys[code].get();
		}

		void setAxis(const string& code, Control::Axis* key)
		{
			axis[code] = std::unique_ptr<Control::Axis>(key);
		}
		Control::Axis* getAxis(const string& code)
		{
			return axis[code].get();
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Control::MultiKey>> keys;
		std::unordered_map<std::string, std::unique_ptr<Control::Axis>> axis;


	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}