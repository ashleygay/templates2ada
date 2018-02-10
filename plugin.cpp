#include <iostream>

/* All plugin sources should start including "gcc-plugin.h".  */
#include "gcc-plugin.h"
/* This let us inspect the GENERIC intermediate representation.  */
#include "tree.h"

/* All plugins must export this symbol so that they can be linked with
   GCC license-wise.  */
int plugin_is_GPL_compatible;


static void pragma_template(void *gcc_data, void *user_data)
{
	if (gcc_data) {
		tree t = (tree)gcc_data;
		std::cout << "PRAGMA" << std::endl;
		std::cout << "TREE_CODE_NAME: "<< get_tree_code_name(TREE_CODE(t)) << std::endl;
	}
}

static void dump_functions(void *gcc_data, void *user_data)
{
	//std::cout << "Dump function is triggered" << std::endl;
//	(void)gcc_data;
	(void)user_data;

	// Not a pointer because tree is a typedef to a pointed type
	tree t = (tree)gcc_data;

	if (IS_TYPE_OR_DECL_P(t)) {
		std::cout << "DATA: "<< (void*)t << std::endl;
		std::cout << "TREE_CODE_NAME: "<< get_tree_code_name(TREE_CODE(t)) << std::endl;
		std::cout << "function" << std::endl;
	}
	else {
//		std::cout << "not function" << std::endl;
	}
}

/* Most interesting part so far: this is the plugin entry point.  */
int plugin_init (struct plugin_name_args *plugin_info,
		 struct plugin_gcc_version *version)
{
	(void) version;

	const char *plugin_name = plugin_info->base_name;
	struct plugin_info pi = { "0.1", "Enum binder plugin" };
	register_callback (plugin_name, PLUGIN_INFO, NULL, &pi);

	register_callback (plugin_name, PLUGIN_START_PARSE_FUNCTION,
			   &dump_functions, NULL);

	register_callback (plugin_name, PLUGIN_PRAGMAS,
			   &pragma_template, NULL);

	return 0;
}
