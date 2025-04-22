#pragma once
#include <unordered_map>
namespace nodes {
  class NodeFactory {

	protected:
		std::unordered_map<void *, lingodb::location> locations;
	public:
		template<class T, class... Args>
		auto node(lingodb::location loc, Args... args) -> std::shared_ptr<T> {
			auto node = std::make_shared<T>(std::forward<Args>(args)...);

			locations[node.get()] = loc;
			return std::move(node);
		}
  		template<class T>
  		auto list(lingodb::location loc) -> std::vector<T>  {
			std::vector<T> nodes{};
			return nodes;
		}

		/*auto notNode(yy::location loc, Args...args) -> UnaryOp* {
			T* ptr = node<T>(loc, std::forward<Args>(args)...);
			return node<UnaryOp>(loc, UnaryOp::Op::NOT, ptr);
		}*/
		void clear() {
			locations.clear();
		}

	};
}
