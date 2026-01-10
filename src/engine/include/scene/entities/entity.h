#ifndef ENTITY_H
#define ENTITY_H


#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>

#include <scene/components.h>

struct Entity {
    public:
        Entity() = default;

        const std::string GetUUID() const { return this->m_id; }

        template <typename T, typename... Args>
        void AddComponent(Args&&... args);

        template <typename T>
        T* GetComponent() {
            auto type = std::type_index(typeid(T));
            auto iterator = components.find(type);

            if (iterator == components.end()) {
                return nullptr;
            }

            return static_cast<T*>(iterator->second.get());
        }

        template <typename T>
        bool HasComponent() const {
            return components.count(std::type_index(typeid(T))) > 0;
        }

    private:
        const std::string m_id;
        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#endif