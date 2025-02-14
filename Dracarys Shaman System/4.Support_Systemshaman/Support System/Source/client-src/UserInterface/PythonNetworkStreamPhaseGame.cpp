# Search

			case HEADER_GC_SPECIFIC_EFFECT:
				ret = RecvSpecificEffect();
				break;

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
			case HEADER_GC_SUPPORT_SKILL:
				ret = RecvSupportUseSkill();
				break;
#endif