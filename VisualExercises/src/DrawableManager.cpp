#include <DrawableManager.hpp>

namespace ve
{
    DrawableManager::DrawableManager(sf::RenderWindow& window)
        : idGenerator{ 0 }
        , window{ window }
    {

    }

    void DrawableManager::add(const DrawablePtr& entity, const ZIndex zIndex)
    {
        layers[zIndex].emplace(idGenerator, entity);
        entity->setId(idGenerator++);
    }

    void DrawableManager::remove(const Id id)
    {
        for (auto& layer : layers)
        {
            if (layer.second.find(id) != layer.second.end())
            {
                layer.second.erase(id);
                break;
            }
        }
    }

    void DrawableManager::remove(const Id id, const ZIndex zIndex)
    {
        auto layer = layers.find(zIndex);
        if (layer == layers.end())
        {
            return;
        }
        layer->second.erase(id);
    }

#include <SFML/Graphics/Vertex.hpp>

    void DrawableManager::draw()
    {
        for (const auto& layer : layers)
        {
            for (const auto& drawable : layer.second)
            {
                window.draw(*drawable.second->getSfDrawable());
            }
        }
    }

}