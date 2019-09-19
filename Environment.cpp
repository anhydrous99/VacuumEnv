//
// Created by aherrera on 8/31/19.
//

#include <random>
#include <stdexcept>
#include <algorithm>

#include "Environment.h"
#include "custom_assertion.h"

void Environment::recalculate_neighbor_obstacles() {
    for (auto &obj : _data)
        obj.neighborObstacles.clear();
    for (int i = 0; i < _n; i++) {
        int current_row = i * _n;
        for (int j = 0; j < _n; j++) {
            if (_data[current_row + j].contains_obstacle) {
                if (i != 0)
                    _data[(i - 1) * _n + j].neighborObstacles.push_back(cell::RIGHT_OBSTACLE);
                if (i != _n - 1)
                    _data[(i + 1) * _n + j].neighborObstacles.push_back(cell::LEFT_OBSTACLE);
                if (j != 0)
                    _data[current_row + j - 1].neighborObstacles.push_back(cell::UPPER_OBSTACLE);
                if (j != _n - 1)
                    _data[current_row + j + 1].neighborObstacles.push_back(cell::LOWER_OBSTACLE);
            }
        }
    }
}

Environment::Environment(int n) : _n(n), _data(n * n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0)
                _data[0].cellType = cell::NORTHWEST_CORNER_TYPE;
            else if (i == n - 1 && j == 0)
                _data[i * n + j].cellType = cell::SOUTHWEST_CORNER_TYPE;
            else if (i == 0 && j == n - 1)
                _data[i * n + j].cellType = cell::NORTHEAST_CORNER_TYPE;
            else if (i == n - 1 && j == n - 1)
                _data[i * n + j].cellType = cell::SOUTHEAST_CORNER_TYPE;
            else if (i == 0)
                _data[j].cellType = cell::NORTH_BOUNDARY_TYPE;
            else if (i == n - 1)
                _data[i * n + j].cellType = cell::SOUTH_BOUNDARY_TYPE;
            else if (j == 0)
                _data[i * n].cellType = cell::WEST_BOUNDARY_TYPE;
            else if (j == n - 1)
                _data[i * n + j].cellType = cell::EAST_BOUNDARY_TYPE;
        }
    }
}

Environment::Environment(int n, float dirty_percentage) : Environment(n) {
    ASSERT(0.0 <= dirty_percentage <= 1.0, "dirty percentage can only be between 0.0 and 1.0")
    unsigned long n_elements = _data.size();

    if (dirty_percentage == 1.0) {
        std::transform(_data.begin(), _data.end(), _data.begin(), [](cell c) -> cell {
            c.cellValue = cell::DIRTY_VALUE;
            return c;
        });
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n_elements - 1);

    unsigned long n_dirty = static_cast<unsigned>(
            static_cast<float>(n_elements) * dirty_percentage);
    std::vector<int> dirty;
    for (unsigned long i = 0; i < n_dirty; i++) {
        int rn = dis(gen);
        if (std::find(dirty.begin(), dirty.end(), rn) == dirty.end()) {
            dirty.push_back(rn);
            _data[rn].cellValue = cell::DIRTY_VALUE;
        } else {
            i--;
        }
    }
    recalculate_neighbor_obstacles();
}

Environment::Environment(int n, float dirty_percentage, float percentage_obstacle) : Environment(n, dirty_percentage) {
    ASSERT(0.0 <= percentage_obstacle <= 1.0, "percentage obstacle can only between 0.0 and 1.0")
    unsigned long n_elements = _data.size();

    if (percentage_obstacle == 1.0) {
        std::transform(_data.begin(), _data.end(), _data.begin(), [](cell c) -> cell {
            c.contains_obstacle = true;
            c.neighborObstacles.push_back(cell::UPPER_OBSTACLE);
            c.neighborObstacles.push_back(cell::LOWER_OBSTACLE);
            c.neighborObstacles.push_back(cell::RIGHT_OBSTACLE);
            c.neighborObstacles.push_back(cell::LEFT_OBSTACLE);
            return c;
        });
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n_elements - 1);

    unsigned long n_obstacles = static_cast<unsigned>(
            static_cast<float>(n_elements) * percentage_obstacle);
    std::vector<int> obstacle;
    for (unsigned long i = 0; i < n_obstacles; i++) {
        int rn = dis(gen);
        if (std::find(obstacle.begin(), obstacle.end(), rn) == obstacle.end()) {
            obstacle.push_back(rn);
            _data[rn].contains_obstacle = true;
            _data[rn].cellValue = cell::CLEAN_VALUE;
        } else {
            i--;
        }
    }
}

cell &Environment::operator()(int i, int j) {
    ASSERT(0 <= i < _n, "Input i index out of range")
    ASSERT(0 <= j < _n, "Input j index out of range")
    return _data[i * _n + j];
}

cell &Environment::operator()(position p) {
    return operator()(p.first, p.second);
}

void Environment::add_vacuum(int i, int j, const std::string &name) {
    ASSERT(0 <= i < _n, "Input i index out of range")
    ASSERT(0 <= j < _n, "Input j index out of range")
    if (operator()(i, j).contains_obstacle)
        operator()(i, j).contains_obstacle = false;

    if (i == 0 && j == 0) {
        if (operator()(1, 0).contains_obstacle && operator()(1, 0).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (i == 0 && j == _n - 1) {
        if (operator()(1, _n - 1).contains_obstacle && operator()(0, _n - 2).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (i == _n - 1 && j == 0) {
        if (operator()(_n - 2, 0).contains_obstacle && operator()(_n - 1, 1).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (i == _n - 1 && j == _n - 1) {
        if (operator()(_n - 2, _n - 1).contains_obstacle && operator()(_n - 1, _n - 2).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (i == 0) {
        if (operator()(0, j - 1).contains_obstacle && operator()(0, j + 1).contains_obstacle &&
            operator()(1, j).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (i == _n - 1) {
        if (operator()(_n - 1, j - 1).contains_obstacle && operator()(_n - 1, j + 1).contains_obstacle &&
            operator()(_n - 2, j).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else if (j == 0) {
        if (operator()(i - 1, 0).contains_obstacle && operator()(i + 1, 0).contains_obstacle &&
            operator()(i, 1).contains_obstacle)
            throw std::runtime_error("No path form vacuum location");
    } else if (j == _n - 1) {
        if (operator()(i - 1, _n - 1).contains_obstacle && operator()(i + 1, _n - 1).contains_obstacle &&
            operator()(i, _n - 2).contains_obstacle)
            throw std::runtime_error("No path from vacuum location");
    } else {
        if (operator()(i - 1, j).contains_obstacle && operator()(i + 1, j).contains_obstacle &&
            operator()(i, j - 1).contains_obstacle && operator()(i, j + 1).contains_obstacle)
            throw std::runtime_error("No paht form vacuum location");
    }

    _vacuums.emplace(std::make_pair(std::string(name), vacuum(i, j)));
}

vacuum &Environment::access_vacuum(const std::string &name) {
    ASSERT(_vacuums.find(name) != _vacuums.end(), "Vacuum " + name + " not found")
    return _vacuums[name];
}

void Environment::move_vacuum(const std::string &name, char direction, char clean) {
    ASSERT(direction == 'N' || direction == 'W' || direction == 'E' || direction == 'S', "Invalid direction")
    ASSERT(clean == '0' || clean == 'C' || clean == 'D', "Invalid cleaning entry")

    auto search = _vacuums.find(name);
    ASSERT(search != _vacuums.end(), "Vacuum " + name + " not found")

    vacuum current_vacuum = search->second;
    position p = current_vacuum.get_position();
    cell &current_cell = operator()(p.first, p.second);

    current_cell.has_been_transvered = true;

    if (clean == 'D') {
        current_cell.cellValue = cell::CLEAN_VALUE;
        return;
    }

    switch (current_cell.cellType) {
        case cell::EAST_BOUNDARY_TYPE:
            ASSERT(direction != 'E', "Can't go east when at the east border")
            break;
        case cell::WEST_BOUNDARY_TYPE:
            ASSERT(direction != 'W', "Can't go west when at the west border")
            break;
        case cell::NORTH_BOUNDARY_TYPE:
            ASSERT(direction != 'N', "Can't go north when at the northern border")
            break;
        case cell::SOUTH_BOUNDARY_TYPE:
            ASSERT(direction != 'S', "Can't go south when at the southern border")
            break;
        case cell::NORTHWEST_CORNER_TYPE:
            ASSERT(direction != 'N' && direction != 'W', "Can't go northwest when at the northwest corner")
            break;
        case cell::NORTHEAST_CORNER_TYPE:
            ASSERT(direction != 'N' && direction != 'E', "Can't go northeast when at the northeast corner")
            break;
        case cell::SOUTHWEST_CORNER_TYPE:
            ASSERT(direction != 'S' && direction != 'W', "Can't go southwest when at the southwest corner")
            break;
        case cell::SOUTHEAST_CORNER_TYPE:
            ASSERT(direction != 'S' && direction != 'E', "Can't go southeast when at the southeast corner")
            break;
        default:;
    }

    if (direction == 'W') {
        cell neighbor = operator()(p.first, p.second - 1);
        ASSERT(!neighbor.contains_obstacle, "There is an obstacle here")
        p.second--;
    } else if (direction == 'E') {
        cell neighbor = operator()(p.first, p.second + 1);
        ASSERT(!neighbor.contains_obstacle, "There is an obstacle here")
        p.second++;
    } else if (direction == 'N') {
        cell neighbor = operator()(p.first - 1, p.second);
        ASSERT(!neighbor.contains_obstacle, "There is an obstacle here")
        p.first--;
    } else {
        cell neighbor = operator()(p.first + 1, p.second);
        ASSERT(!neighbor.contains_obstacle, "There is an obstacle here")
        p.first++;
    }

    search->second.set_position(p);
}

bool Environment::step_vacuum(const std::string &vacuum_name) {
    Environment current_environment = *this;
    std::string ret = agent_function(vacuum_name, current_environment);
    char clean = ret[0];
    ASSERT(clean == 'C' || clean == 'D' || clean == '0', "Invalid cleaning entry")
    move_vacuum(vacuum_name, ret[1], clean);
    return check_all_clean();
}

bool Environment::step_vacuums() {
    bool is_clean = check_all_clean();
    if (is_clean)
        return is_clean;
    for (const auto &p : _vacuums)
        is_clean = step_vacuum(p.first);
    return is_clean;
}

void Environment::add_agent_function(const std::function<std::string(const std::string &, Environment &)> &func) {
    agent_function = func;
}

cell &Environment::operator[](int i) {
    ASSERT(0 <= i < _n * _n, "Out of bounds")
    return _data[i];
}

bool Environment::check_all_clean() {
    for (int i = 0; i < _n * _n; i++) {
        if (!_data[i].contains_obstacle) {
            if (_data[i].cellValue == cell::DIRTY_VALUE)
                return false;
        }
    }
    return true;
}

int Environment::side_size() {
    return _n;
}

cell *Environment::data() {
    return _data.data();
}

std::ostream &operator<<(std::ostream &os, const Environment &environment) {
    int n = environment._n;
    std::vector<position> vacuum_position;

    std::transform(environment._vacuums.begin(), environment._vacuums.end(), std::back_inserter(vacuum_position),
                   [](std::pair<std::string, vacuum> x) -> position { return x.second.get_position(); });

    for (int i = 0; i < n; i++) {
        int current_row = i * n;
        for (int j = 0; j < n; j++) {
            bool found =
                    std::find(vacuum_position.begin(), vacuum_position.end(), position(i, j)) != vacuum_position.end();
            os << environment._data[current_row + j] << ((found) ? "\033[36m⬅\033[0m" : " ");
        }
        os << std::endl;
    }
    return os;
}