# Add

bool LEVEL_DELTA(int iLevel, int yLevel, int iDifLev)
{
	return ((iLevel - iDifLev <= yLevel) && (iLevel + iDifLev >= yLevel));
}
