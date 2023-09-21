#include <Platform/types.h>
namespace Machi {

	namespace DataStructure {

		class Node {

			Node* output;
			Node* input;


			void link_to(MSTRING& name, Node* other);
			void link_from(MSTRING& name, Node* other);


		};

	}
}