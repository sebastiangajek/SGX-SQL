ALL_CUSTOM_MK=$(shell find . -name '*sgx_t_u.mk')



.PHONY: all clean run


all clean:
	$(foreach U_MK, $(ALL_CUSTOM_MK), $(MAKE) -C $(shell dirname $(U_MK))  -f $(shell basename $(U_MK)) $@;)

run:
	$(foreach U_MK, $(ALL_CUSTOM_MK), $(MAKE) -C $(shell dirname $(U_MK))   -f $(shell basename $(U_MK)) $@;)

