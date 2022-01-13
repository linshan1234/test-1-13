<template>
    <button type="button" class="app-wrapper display_center_start" ref="app"
        v-show="c_show"
        @focus="toggleBtnWindow(WINDOW_APP, true)"
        @blur="toggleBtnWindow(WINDOW_APP, false)">
        <div class="icon icon-app"></div>
        <div class="breadcrumb-block"><span class="text">{{$t(breadcrumb)}}</span></div>
        <div class="icon icon-arrow"></div>
        <div class="app-option-wrapper display_center_start" v-show="c_showAppOption"
          :style="{width: app.width + 'vw'}">
          <Gap :width="app.width - 0.10416666666666667 + 'vw'" :height="'0.7407407407407408vh'" :bgcColor="'#ffffff'" />
          <div class="option-wrapper" 
            v-for="(data, index) in app.data" :key="index" v-show="data.show"
            :style="{width: app.width - 0.10416666666666667 + 'vw'}">
            <div class="option-title display_center_start"><span class="text">{{ $t(data.title) }}</span></div>
            <div class="option-block display_center_start" v-show="option.show"
              v-for="(option, index) in data.options" :key="index"
              :class="{active: currentPage == option.value}"
              @click.stop="onAppOptionClick(option)">
              <div class="icon-check-block display_center_start">
                <div class="icon icon-check" v-show="currentPage == option.value"></div></div>
              <div class="option-text display_center_start"><span class="text">{{ $t(option.text) }}</span></div>
          </div>
          </div>
          <Gap :width="app.width - 0.10416666666666667 + 'vw'" :height="'0.7407407407407408vh'" :bgcColor="'#ffffff'" />
        </div>
    </button>
</template>

<script>
import Gap from '~/components/Gap/Gap.vue'
import { isObject, } from '~/store/share'
export default {
    name: 'AppSelect',
    components: { Gap },
    props: {
        show: { type: Boolean, default: false },
        showAppOption: { type: Boolean, default: false },
        WINDOW_APP: { type: String, default: '' },
        ROUTER_INSIGHTAPM: { type: String, default: '' },
        toggleWindow: { type: String, default: 'toggleWindow' },
    },
    data () {
        return {
            c_show: this.show,
            c_showAppOption: this.showAppOption,
            app: {
                width: 13.229166666666666,
                value: '',
                data: [
                  { title: 'Basic Settings', show: true, options: [
                    { value: 'Home', url: '/Home', text: 'breadcrumb.Home', show: true, },
                    { value: 'ExceptionHandle', url: '/ExceptionHandle', text: 'breadcrumb.ExceptionHandle', show: true, },
                    { value: 'FixReport', url: '/FixReport', text: 'breadcrumb.FixReport', show: true, },
                    { value: 'Maintenance', url: '/Maintenance', text: 'breadcrumb.Maintenance', show: true, },
                    { value: 'Production', url: '/Production', text: 'breadcrumb.Production', show: true, },
                    { value: 'ManageConfig', url: '/ManageConfig', text: 'breadcrumb.ManageConfig', show: true, },
                  ], },
                  { title: 'I.Apps', show: true, options: [
                    { value: 'InsightAPM', url: '', text: 'WISE-PaaS/insightAPM', show: true, },
                  ], },
                ],
            }
        }
    },
    watch: {
        show (boolean) { this.c_show = boolean },
        showAppOption (boolean) { this.c_showAppOption = boolean },
    },
    methods: {
        onAppOptionClick (data) {
            if (!isObject(data)) return
            data.value ==  this.ROUTER_INSIGHTAPM 
              ? window.location.href = this.insigihtAPM 
              : this.$router.push(data.url)
            this.$refs.app.blur()
        },
        toggleBtnWindow (whichWindow, boolean) { this.$emit(this.toggleWindow, whichWindow, boolean) }
    },
    computed: {
        currentPage () { return this.$store.state.currentPage },
        breadcrumb () { return 'breadcrumb.' + this.currentPage },
        insigihtAPM () { return this.$store.state.m2i.domain },
    }
}
</script>