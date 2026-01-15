#ifndef ENTITY_H
#define ENTITY_H


#include <atomic>

static std::atomic<uint64_t> counter{0};

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
        T* GetComponent();

        template <typename T>
        bool HasComponent() const;

    private:
        const std::string m_id;
        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#endif