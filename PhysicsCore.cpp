#include "PhysicsCore.h"
#include "GravityPoint.h"

// TODO move those functions to the header
// float vec_mod(const sf::Vector2f& pt)
// {
    // return std::sqrt(pt.x * pt.x + pt.y * pt.y);
// }

// void normalize(sf::Vector2f& pt, float mod)
// {
    // pt.x /= mod;
    // pt.y /= mod;
// }

PhysicsCore::PhysicsCore(
        ParticlesContainer & particles,
        IChunkGenerator & chunk_generator,
        const sf::Vector2f& window_br_border)
    : m_br_border(sf::Vector2f(window_br_border.x - window_margin_px, window_br_border.y - window_margin_px))
    , m_tl_border(window_margin_px, window_margin_px)
    , m_window_br_border(window_br_border)
    , m_particles(particles)
    , m_chunk_generator(chunk_generator)
    , m_worker([this]{ while (!m_thread_stopped) { calculate(); } })
{
}

PhysicsCore::~PhysicsCore()
{
    m_thread_stopped = true;
    m_worker.join();
}

void PhysicsCore::calculate()
{
    const auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double> time_diff = now - m_previous_calculation;
    const float time_coef = time_diff.count();
    m_previous_calculation = now;

    std::vector<Particle *> dead_particles;

    sf::Vector2f gravity_acceleration(0, gravity_coef);
    m_particles.for_each_chunk([&](auto & chunk) {
        dead_particles.clear();
        for (auto & p : chunk.particles()) {
            if (!p.is_alive(now)) {
                dead_particles.push_back(&p);
                continue;
            }
            p.m_velosity += gravity_acceleration * time_coef;

            p.shape().position += (p.m_velosity * time_coef);
            handle_border_crossing(p);
        }
        for (auto * p : dead_particles) {
            chunk.mark_as_dead(*p);
            m_chunk_generator.on_particle_died(chunk, p->shape().position);
        }
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
