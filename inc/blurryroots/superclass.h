#ifndef superclass_h
#define superclass_h

// allows for super class referencing without
// having to care about the type name
#define DECLARE_SUPER_CLASS(super_class) \
	private: typedef super_class __super

#endif
