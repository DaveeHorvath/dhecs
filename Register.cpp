#include <variant>
#include <unordered_map>
#include <vector>

namespace DHecs
{
	template <typename... cmps>
	class Registry
	{
	using component_type = std::type_index;
	using component_id = uint32_t;
	using entity_id = uint32_t;
	std::variant<cmps> component;
	using entity = std::vector<component>
	public:
		template<typename cp>
		component_type getComponentType()
		{
			return std::type_index(typeof(cp));
		}

		template<typename cp>
		std::vector<component_id> getComponentIds()
		{
			component_type t = getComponentType<cp>();
			std::vector<std::pair<component_id, entity_id>> fitting = _registry[t];
			std::vector<component_id> ids = std::vector<component_id>(fitting.size());
			
			for (size_t i = 0; i < fitting.size(); i++)
				ids[i] = fitting[i].first;
			return ids;
		}

		template<typename cp>
		std::vector<entity_id> getEntityIds()
		{
			component_type t = getComponentType<cp>();
			std::vector<std::pair<component_id, entity_id>> fitting = _registry[t];
			std::vector<entity_id> ids = std::vector<entity_id>(fitting.size());
			
			for (size_t i = 0; i < fitting.size(); i++)
				ids[i] = fitting[i].second;
			return ids;
		}

		template<typename cp>
		component_id getFirstComponentId()
		{
			component_type t = getComponentType<cp>();
			std::vector<std::pair<component_id, entity_id>> fitting = _registry[t];
			
			return fitting[0].first;
		}

		template<typename cp>
		component_id getFirstEntityId()
		{
			component_type t = getComponentType<cp>();
			std::vector<std::pair<component_id, entity_id>> fitting = _registry[t];
			
			return fitting[0].second;
		}
		
	private:
		std::unordered_map<component_type, std::vector<std::pair<component_id, entity_id>>> _registry;
		std::vector<component> _components;
		std::vector<entity> _entities;
	};
};

int main()
{

}