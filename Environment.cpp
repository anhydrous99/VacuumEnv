//
// Created by aherrera on 8/31/19.
//

#include <random>
#include <algorithm>
#include <cassert>

#include "Environment.h"

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
            else if (i == 0 && j == n - 1)
                _data[i * n + j].cellType = cell::NORTHEAST_CORNER_TYPE;
            else if (i == n - 1 && j == 0)
                _data[i * n + j].cellType = cell::SOUTHWEST_CORDER_TYPE;
            else if (i == n - 1 && j == n - 1)
                _data[i * n + j].cellType = cell::NORTHEAST_CORNER_TYPE;
            else if (i == 0)
                _data[i * n + j].cellType = cell::NORTH_BOUNDARY_TYPE;
            else if (i == n - 1)
                _data[i * n + j].cellType = cell::SOUTH_BOUNDARY_TYPE;
            else if (j == 0)
                _data[i * n + j].cellType = cell::WEST_BOUNDARY_TYPE;
            else if (j == n - 1)
                _data[i * n + j].cellType = cell::EAST_BOUNDARY_TYPE;
        }
    }
}

Environment::Environment(int n, float dirty_percentage) : Environment(n) {
    assert(0.0 <= dirty_percentage <= 1.0);
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
    assert(0.0 <= percentage_obstacle <= percentage_obstacle);
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

    unsigned long n_dirty = static_cast<unsigned>(
            static_cast<float>(n_elements) * dirty_percentage);
    std::vector<int> dirty;
    for (unsigned long i = 0; i < n_dirty; i++) {
        int rn = dis(gen);
        if (std::find(dirty.begin(), dirty.end(), rn) == dirty.end()) {
            dirty.push_back(rn);
            _data[rn].contains_obstacle = true;
        } else {
            i--;
        }
    }
}

cell &Environment::operator()(int i, int j) {
    assert(i < _n);
    assert(j < _n);
    return _data[i * _n + j];
}

void Environment::add_vacuum(int i, int j, const std::string &name) {
    assert(i < _n);
    assert(j < _n);
    _vacuums.emplace(std::make_pair(std::string(name), vacuum(i, j)));
}

vacuum &Environment::access_vacuum(const std::string &name) {
    assert(_vacuums.find(name) != _vacuums.end());
    return _vacuums[name];
}

void Environment::move_vacuum(const std::string &name, char direction) {
    assert(direction == 'N' ||
           direction == 'W' ||
           direction == 'E' ||
           direction == 'S');
    auto search = _vacuums.find(name);
    assert(search != _vacuums.end());

    vacuum current_vacuum = _vacuums[name];
    position p = current_vacuum.get_position();
    cell current_cell = operator()(p.first, p.second);

    switch (current_cell.cellType) {
        case cell::EAST_BOUNDARY_TYPE:
            assert(direction != 'W');
            break;
        case cell::WEST_BOUNDARY_TYPE:
            assert(direction != 'E');
            break;
        case cell::NORTH_BOUNDARY_TYPE:
            assert(direction != 'N');
            break;
        case cell::SOUTH_BOUNDARY_TYPE:
            assert(direction != 'S');
            break;
        case cell::NORTHWEST_CORNER_TYPE:
            assert(direction != 'N' && direction != 'W');
            break;
        case cell::NORTHEAST_CORNER_TYPE:
            assert(direction != 'N' && direction != 'E');
            break;
        case cell::SOUTHWEST_CORDER_TYPE:
            assert(direction != 'S' && direction != 'W');
            break;
        case cell::SOUTHEAST_CORNER_TYPE:
            assert(direction != 'S' && direction != 'E');
            break;
        default:;
    }

    if (direction == 'W')
        p.first--;
    else if (direction == 'E')
        p.first++;
    else if (direction == 'N')
        p.second++;
    else
        p.second--;

    search->second.set_position(p);
}

void Environment::step_vacuum(const std::string &vacuum_name) {
    Environment current_environment = *this;
    _vacuums[vacuum_name] = agent_function(vacuum_name, current_environment);
}

void Environment::step_vacuums() {
    for (const auto &p : _vacuums)
        step_vacuum(p.first);
}

cell &Environment::operator[](int i) {
    assert(i < _n * _n);
    return _data[i];
}

bool Environment::check_all_clean() {
    for (const cell &c : _data)
        if (!c.contains_obstacle)
            if (c.cellValue == cell::DIRTY_VALUE)
                return false;
    return true;
}

cell *Environment::data() {
    return _data.data();
}

std::ostream &operator<<(std::ostream &os, const Environment &environment) {
    int n = environment._n;
    for (int i = 0; i < n; i++) {
        int current_row = i * n;
        for (int j = 0; j < n; j++) {
            os << environment._data[current_row + j] << " ";
        }
        os << std::endl;
    }
    return os;
}