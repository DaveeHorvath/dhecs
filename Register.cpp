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
	using entity = std::vector<component_id>
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
		std::vector<cp> getComponents()
		{
			std::vector<component_id> ids = getComponentIds<cp>();
			std::vector<cp> res;

			res.reserve(ids.size());
			std::for_each(ids.begin(), ids.end(), [&](component_id& id){ res.push_back(_components.find(id)); });
			return res;
		}

		template<typename cp>
		cp getComponent(entity_id entity)
		{
			std::vector<component_id> ids = _entities[entity];

			return std::find(ids.begin(), ids.end(), [&](component_id& id){ return std::type_index(typeof(cp)) == std::type_index(typeof(_components[id])); });
		}

		/* subject to change as the entity / component containers arent fixed yet */
		void addComponent(entity_id entity, component c)
		{
			const component_id comp_id = _components.size();
			_entities[entity].push_back(comp_id);
			_components.insert(comp_id, c);
			std::pair<component_id, entity_id> tmp{comp_id, emtity};
			_registry[std::type_index(typeof(c))].push_back(tmp);
		}
		
	private:
		std::unordered_map<component_type, std::vector<std::pair<component_id, entity_id>>> _registry;
		std::unordered_map<component_id, component> _components;
		std::unordered_map<entity_id, entity> _entities;
	};
};

int main()
{

}