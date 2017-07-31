#pragma once

#include <array>
#include <cstdint>
#include <iostream>

#include <yatc/rotation.h>


namespace yatc {
    /*! \brief Class for 2D integer coordinates.
     */
    class coordinate final {
    public:
        using type = std::int8_t;

        /*! \brief Creates 2d point */
        explicit coordinate(const type x = 0, const type y = 0);

        coordinate(coordinate&&) = default;
        coordinate(const coordinate&) = default;
        coordinate& operator=(coordinate&&) = default;
        coordinate& operator=(const coordinate&) = default;

        /*! \brief First component accessor.
         *  \return Reference to first component.
         */
        type& x() { return m_data[0]; }

        /*! \brief First component accessor.
         *  \return Value of first component.
         */
        type x() const { return m_data[0]; }

        /*! \brief Second component accessor.
         *  \return Reference to second component.
         */
        type& y() { return m_data[1]; }

        /*! \brief Second component accessor.
         *  \return Value of second component.
         */
        type y() const { return m_data[1]; }

        /*! \brief Translates coordinate by vector given in other.
         *  \param other translation vector
         *  \return This coordinates moved by other vector.
         */
        coordinate& operator+=(const coordinate& other);

        /*! \brief Translates coordinate by vector given in other.
         *  \param other translation vector
         *  \return This coordinates moved by -other vector.
         */
        coordinate& operator-=(const coordinate& other);

        /*! \brief Rotates point for 90deg around {0, 0}.
         *  \param d direction of rotation.
         */
        void rotate(const rotation dir);
    private:
        std::array<type, 2>    m_data;
    };

    /*! \brief Negates components of given coordinates.
     *  \param c coordinates to negate
     *  \return Coordinates with negated components.
     */
    coordinate operator-(const coordinate& c);

    /*! \brief Translates coordinates a by vector b.
     *  \param a coordinates to translate
     *  \param b translation vector
     *  \return a coordinates moved by vector b.
     */
    coordinate operator+(coordinate a, const coordinate& b);

    /*! \brief Translates coordinates a by vector -b.
     *  \param a coordinates to translate
     *  \param b translation vector
     *  \return a coordinates moved by vector -b.
     */
    coordinate operator-(coordinate a, const coordinate& b);

    /*! \brief Comprison.
     *  \param a first coordinates
     *  \param b second coordinates
     *  \return true if a.x == b.x and a.y == by.
     */
    bool operator==(const coordinate& a, const coordinate& b);

    /*! \brief Comprison.
     *  \param a first coordinates
     *  \param b second coordinates
     *  \return true if a.x != b.x or a.y != by.
     */
    bool operator!=(const coordinate& a, const coordinate& b);

    /*! \brief Rotation by 90deg.
     *  \param c coordinates to rotate
     *  \param dir rotation direction
     *  \return c coordinates rotated around {0, 0} by 90dec in direction dir.
     */
    coordinate rotate(coordinate c, const rotation dir);

    /*! \brief Outputs coordinates to output stream.
     *  \param os output stream
     *  \param c coordinated
     *  \return os stream with coordinates c output to it.
     */
    std::ostream& operator<<(std::ostream& os, const coordinate& c);
}
