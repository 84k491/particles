#include "PhysicsCore.h"

#include "GravityPoint.h"
#include "ParticleChunk.h"

PhysicsCore::PhysicsCore(
        IList<ParticleChunk> & particles,
        IChunkGenerator & chunk_generator,
        const sf::Vector2f& window_br_border)
    : m_br_border(sf::Vector2f(window_br_border.x - window_margin_px, window_br_border.y - window_margin_px))
    , m_tl_border(window_margin_px, window_margin_px)
    , m_window_br_border(window_br_border)
    , m_particles(particles)
    , m_chunk_generator(chunk_generator)
    , m_worker([this]{  calculate(); })
{
}

void PhysicsCore::calculate()
{
    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double> time_diff = now - m_previous_calculation_time;
    const float time_coef = time_diff.count();
    m_previous_calculation_time = now;

    sf::Vector2f gravity_acceleration(0, gravity_coef);

    m_particles.foreach([&](ParticleChunk & chunk) -> bool {
        chunk.for_each_alive_particle([&](auto & p) -> bool {
            if (!p.is_alive()) {
                if (p.will_spawn_new()) {
                    m_chunk_generator.generate_chunk(p.shape().position);
                }
                return true;
            }
            p.m_velosity += gravity_acceleration * time_coef;

            p.shape().position += (p.m_velosity * time_coef);
            handle_border_crossing(p);

            return false;
        });
        const auto alive_count = chunk.alive_count();
        // std::cout << "alive_count" << alive_count << std::endl;
        return alive_count == 0;
    });
}

BorderCrossing PhysicsCore::if_out_of_borders(const Particle& p) const
{
    const auto& pos = p.shape().position;
    if (pos.x > m_br_border.x) {
        return BorderCrossing::Right;
    }
    if (pos.y > m_br_border.y) {
        return BorderCrossing::Bottom;
    }
    if (pos.x < m_tl_border.x) {
        return BorderCrossing::Left;
    }
    if (pos.y < m_tl_border.y) {
        return BorderCrossing::Top;
    }
    return BorderCrossing::None;
}

void PhysicsCore::handle_border_crossing(Particle& p) const
{
    const auto crossed = if_out_of_borders(p);

    switch (crossed) {
    case BorderCrossing::Top:
    case BorderCrossing::Bottom:
        p.m_velosity.y = -p.m_velosity.y;
        break;
    case BorderCrossing::Left:
    case BorderCrossing::Right:
        p.m_velosity.x = -p.m_velosity.x;
        break;
    case BorderCrossing::None:
    default:
        return;
    };
}
