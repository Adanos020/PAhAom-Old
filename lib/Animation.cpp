////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
//
// Note from the PAhAom author:
// The only thing I have changed here is the code formatting.
// Whole code here is written by Maximilian Wagenbach (aka. Foaly)
// mentioned in the notice above.
//
//////////////////////////////////////////////////////////// 

#include "Animation.hpp"

namespace sf {

    Animation::Animation() :
      m_texture(NULL) {}

    void
    Animation::addFrame(sf::IntRect rect)
    {
        m_frames.push_back(rect);
    }

    void
    Animation::clearFrames()
    {
        m_frames.clear();
    }

    void
    Animation::setSpriteSheet(const sf::Texture& texture)
    {
        m_texture = &texture;
    }

    const sf::Texture*
    Animation::getSpriteSheet() const
    {
        return m_texture;
    }

    std::size_t
    Animation::getSize() const
    {
        return m_frames.size();
    }

    const sf::IntRect&
    Animation::getFrame(std::size_t n) const
    {
        return m_frames[n];
    }

    bool
    Animation::operator==(const Animation& right) const
    {
        return m_frames  == right.m_frames
            && m_texture == right.m_texture;
    }

    bool
    Animation::operator!=(const Animation& right) const
    {
        return m_frames  != right.m_frames
            || m_texture != right.m_texture;
    }

}
