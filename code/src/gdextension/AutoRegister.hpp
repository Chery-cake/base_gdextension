#ifndef SRC_GDNATIVE_CLASS_AUTOREGISTER_HPP_
#define SRC_GDNATIVE_CLASS_AUTOREGISTER_HPP_

#include <godot_cpp/core/class_db.hpp>
#include <type_traits>

#include "Register.hpp"

#define REGISTER_CLASS(MAIN_CLASS, BASE_CLASS) static inline bool m_register = AutoRegister::register_class<MAIN_CLASS>();\
	GDCLASS(MAIN_CLASS, BASE_CLASS);

class AutoRegister {
private:

	static std::vector<void (*)()>& m_init_funcs() {
		static std::vector<void (*)()> instance;
		return instance;
	}

	static std::vector<void (*)()>& m_init_module_funcs() {
		static std::vector<void (*)()> instance;
		return instance;
	}

	static std::vector<void (*)()>& m_uni_module_funcs() {
		static std::vector<void (*)()> instance;
		return instance;
	}

public:

	AutoRegister() = delete;

	template<class B>
	static inline bool register_class() {

		m_init_funcs().push_back([] {
			godot::ClassDB::register_class<B>();
		});

		m_init_module_funcs().push_back([] {
			B::_initialize_module();
		});

		m_uni_module_funcs().push_back([] {
			B::_uninitialize_module();
		});

		return true;
	}

	static void register_initialize_classes() {
		for (auto func : m_init_funcs()) {
			func();
		}
		m_init_funcs().clear();
	}

	static void register_initialize_module() {
		for (auto func : m_init_module_funcs()) {
			func();
		}
		m_init_module_funcs().clear();
	}

	static void register_uninitialize_classes() {
		for (auto func : m_uni_module_funcs()) {
			func();
		}
		m_uni_module_funcs().clear();
	}

};

#endif /* SRC_GDNATIVE_CLASS_AUTOREGISTER_HPP_ */
