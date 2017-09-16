#pragma once
#include <vector>
#include <memory>


/// Usage: inherit from binary tree and as Ty write inheriting class name
///		ParentTy should be equal to Ty or be its base class
template< typename Ty, typename ParentTy = Ty>
class BinaryTree
{
public:

	////// creation

	/// add child above
	void addUp(Ty *s)
	{
		if (childUp == nullptr)
		{
			parent = this;
			childUp = unique_ptr<Ty>(s);
		}
		else
			childUp->addSibling(s);
	}
	/// add child under
	void addDown(Ty *s)
	{
		if (childDown == nullptr)
		{
			parent = this;
			childDown = unique_ptr<Ty>(s);
		}
		else
			childDown->addSibling(s);
	}


	void setParent(ParentTy* s) { parent = s; }

	////// getters

	Ty* getChildUp() const { return childUp.get(); }
	Ty* getChildDown() const { return childUp.get(); }
	Ty* getSibling() const { return childUp.get(); }

	ParentTy* getParent() const { return parent; }


	////// utility

	/// puts ptrs to each child in specific order

	/// me -> child down -> child up -> sibling
	void rewriteTo_Dfs(std::vector<Ty*>& v);
	/// me -> sibling -> child down -> child up
	void rewriteTo_Bfs(std::vector<Ty*>& v);
	/// child down -> me -> sibling -> child up
	void rewriteTo_Rendering(std::vector<Ty*>& v);

private:
	ParentTy* parent;
	/// child can be placed either above or under
	/// which child ptr is used determine rendering order
	std::unique_ptr<Ty> childUp, childDown,
		/// sibling to this model
		/// shows all models on the same layer
		/// Rendering order: first this one then siblings
		sibling;

	/// adds a sibling to the model
	/// for internal purposes
	/// use addUp or addDown instead
	void addSibling(ModelPart *s)
	{
		if (sibling == nullptr)
		{
			sibling = unique_ptr<ModelPart>(s);
			s->parent = parent;
		}
		else
			sibling->addSibling(s);
	}
};
template<typename Ty, typename ParentTy>
void BinaryTree<Ty, ParentTy>::rewriteTo_Dfs(std::vector<Ty*>& v)
{
	v.push_back((Model*)this);

	if (childDown)
		childDown->rewriteToVectorUpdate(v);

	if (childUp)
		childUp->rewriteToVectorUpdate(v);

	if (sibling)
		sibling->rewriteToVectorUpdate(v);
}

template<typename Ty, typename ParentTy>
void BinaryTree<Ty, ParentTy>::rewriteTo_Bfs(std::vector<DoubleTree<Ty*, ParentTy>*>& v)
{
	v.push_back((Model*)this);

	if (sibling)
		sibling->rewriteToVectorUpdate(v);

	if (childDown)
		childDown->rewriteToVectorUpdate(v);

	if (childUp)
		childUp->rewriteToVectorUpdate(v);
}

template<typename Ty, typename ParentTy>
void DoubleTree<Ty, ParentTy>::rewriteTo_Rendering(std::vector<Ty*>& v)
{
	if (childDown)
		childDown->rewriteToVectorUpdate(v);

	v.push_back((Model*)this);

	if (sibling)
		sibling->rewriteToVectorUpdate(v);

	if (childUp)
		childUp->rewriteToVectorUpdate(v);
}