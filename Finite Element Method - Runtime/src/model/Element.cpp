#include "pch.h"

#include "Element.h"

Element::Element()
{
	m_Nodes.reserve(ELEMENT_NODES_SIZE);
	m_Jacobians.resize(INTEGRATION_POINTS_COUNT);
}

void Element::AddNode(int nodeID, Node node)
{
	// TODO: Nodes should not be stored twice
	// For now, nodes are stored twice. Once in Grid and second time in Element. It is because of calculating the Jacobian.
	// This should be changed in future
	m_Nodes.insert({nodeID, node});
}

void Element::CalculateJacobian()
{
	int i = 0;
	for (auto& jacobian : m_Jacobians)
		jacobian.Calculate(m_Nodes, i++);
}

void Element::DisplayJacobians()
{
	int i = 1;
	for (auto& jacobian : m_Jacobians)
	{
		std::cout << "Jacobian in " << i++ << " integration point:\n";
		std::cout << jacobian << "\n";
	}
}

std::ostream& operator<<(std::ostream& os, const Element& element)
{
	os << "{";

	for (auto it = element.m_Nodes.begin(); it != element.m_Nodes.end(); it++)
	{
		os << (*it).first;
		if (std::next(it) != element.m_Nodes.end())
			os << ", ";
	}

	os << "}";

	return os;
}
