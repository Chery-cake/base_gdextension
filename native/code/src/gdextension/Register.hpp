#ifndef SRC_GDEXTENSION_REGISTER_HPP_
#define SRC_GDEXTENSION_REGISTER_HPP_

#include "AutoRegister.hpp"

template<typename G>
class Register : public G{
//	REGISTER_CLASS(B, G);
private:
protected:
public:

	static void _initialize_module() {}

	static void _uninitialize_module() {}

};


#endif /* SRC_GDEXTENSION_REGISTER_HPP_ */
