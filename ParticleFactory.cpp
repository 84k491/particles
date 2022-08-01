#include "ParticleFactory.h"
#include "ParticlesContainer.h"

ParticleFactory::ParticleFactory()
    : m_velosity_randomizer(0.f, 500.f)
    , m_livetime_randomizer(100.f, 2000.f)
    , m_color_randomizer(20.f, 255.f)
{
}

Particle ParticleFactory::create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const
{
    Particle particle(vertex);
    vertex.position = point;
    particle.m_velosity = sf::Vector2f(
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value(),
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value());

    const uint8_t red = std::lround(m_color_randomizer.random_value());
    const uint8_t green = std::lround(m_color_randomizer.random_value());
    constexpr uint8_t blue = 225;
    constexpr uint8_t alpha = 255;
    vertex.color = sf::Color(red, green, blue, alpha);

    particle.m_time_to_die = std::chrono::system_clock::now() +
        std::chrono::milliseconds(1000 + std::lround(m_livetime_randomizer.random_value()));

    return particle;
}

void ParticleFactory::fill_chunk(ParticlesChunk & chunk, const sf::Vector2f & point)
{
    chunk.particles().clear();
    chunk.particles().reserve(chunk.total_size());

    for (size_t i = 0; i < chunk.total_size(); ++i) {
        chunk.particles().emplace_back(create_particle(point, chunk.m_coordinates[i]));
    }

    chunk.m_alive_count = chunk.total_size();
}
