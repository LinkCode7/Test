
#include "ConvertData.h"

#if 0
class TestLineData : public Sindy::IBoundItem
{
public:
	std::string m_strId;
	Point3d m_ptBegin;
	Point3d m_ptEnd;
	double m_dBulge = 0.0;

	Extents m_extents;

	bool GetExtents(double& dMinX, double& dMinY, double& dMaxX, double& dMaxY) override
	{
		Point3d ptMin = m_extents.minPoint();
		dMinX = ptMin.x;
		dMinY = ptMin.y;

		Point3d ptMax = m_extents.maxPoint();
		dMaxX = ptMax.x;
		dMaxY = ptMax.y;
		return true;
	}
};

void convertLine(const std::vector<TestPerformance::TestLineData*>& vecLineData)
{
	Sindy::SQLite sqlite("E:\\Sindy\\intersect\\PixsoTestData.db");
	auto strMsg = sqlite.ErrorMessage();

	sqlite.BeginTransaction();
	sqlite.Prepare("insert into Line values(:1,:2,:3,:4,:5,:6,:7,:8,:9,:10)");

	for (const auto& line : vecLineData)
	{
		sqlite.BindText(":1", line->m_strId);
		sqlite.BindDouble(":2", line->m_dBulge);
		sqlite.BindDouble(":3", line->m_ptBegin.x);
		sqlite.BindDouble(":4", line->m_ptBegin.y);
		sqlite.BindDouble(":5", line->m_ptEnd.x);
		sqlite.BindDouble(":6", line->m_ptEnd.y);

		sqlite.BindDouble(":7", line->m_extents.minPoint().x);
		sqlite.BindDouble(":8", line->m_extents.minPoint().y);
		sqlite.BindDouble(":9", line->m_extents.maxPoint().x);
		sqlite.BindDouble(":10", line->m_extents.maxPoint().y);

		sqlite.Step();
		sqlite.ResetSyntax();
	}
	sqlite.Commit();
}

void convertFormula()
{
	Sindy::SQLite database("E:\\Sindy\\intersect\\TestData.db");
	database.BeginTransaction();
	database.Prepare("select * from Formula");

	std::vector<std::tuple<std::string, std::string, double>> arrInfo;

	while (database.Step() == SQLITE_ROW)
	{
		std::string strFormule;
		database.GetValueText("formula", strFormule);

		std::string strExpression;
		database.GetValueText("expresstion", strExpression);

		double value = 0.0;
		database.GetValueDouble("result", value);

		arrInfo.emplace_back(std::make_tuple(strFormule, strExpression, value));
	}

	if (arrInfo.empty())
		return;


	Sindy::SQLite sqlite("E:\\Sindy\\intersect\\PixsoTestData.db");
	auto strMsg = sqlite.ErrorMessage();

	sqlite.BeginTransaction();
	sqlite.Prepare("insert into Formula values(:1,:2,:3)");

	for (const auto& item : arrInfo)
	{
		sqlite.BindText(":1", std::get<0>(item));
		sqlite.BindText(":2", std::get<1>(item));
		sqlite.BindDouble(":3", std::get<2>(item));

		sqlite.Step();
		sqlite.ResetSyntax();
	}
	sqlite.Commit();
}
#endif
