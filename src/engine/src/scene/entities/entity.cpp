#include <scene/entities/entity.h>

Entity::Entity() : m_id(std::to_string(++counter))
{
    
}

/*

    COMPONENTS

*/

template <typename T, typename ...Args>
void Entity::AddComponent(Args&& ...args) {
    static_assert(std::is_base_of<T, Component>::value, "[ERR] : Unknown Component Type")

    auto type = std::type_index(typeid(T));
    auto component = std::make_unique<T>(std::forward<Args>(args)...);

    this->components[type] = std::move(component);
}

template <typename T>
T* Entity::GetComponent() {
    auto type = std::type_index(typeid(T));
    auto it = this->components.find(type);

    if (it == this->components.end()) {
        return nullptr;
    }

    return static_cast<T*>(it.second.get());
}

template<typename T>
bool Entity::HasComponent() const {
    return this->components.count(std::type_index(typeid(T))) > 0;
}